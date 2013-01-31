#include "communicationresourcegateway.h"

#include "Common/Communication/resourcedownloadnetworkrequest.h"


namespace AW {
namespace Common {
namespace Communication {


CommunicationResourceGateway::CommunicationResourceGateway(CommunicationResourceGatewayDelegate *gatewayDelegate, CommunicationResourceGatewayCacheDelegate *gatewayCacheDelegate, unsigned int maxParallelRequestsCount, QObject *parent) :
    QObject(parent),
    _maxParallelRequestsCount(maxParallelRequestsCount),
    _gatewayDelegate(gatewayDelegate),
    _gatewayCacheDelegate(gatewayCacheDelegate)
{
}

CommunicationResourceGateway::~CommunicationResourceGateway() {
//    this->disconnect(); // not necessary, QObject's destructor does it

    if (_networkRequests.size()) {
        BaseNetworkRequest* request = NULL;
        Q_FOREACH(request, _networkRequests) {
            delete request, request = NULL;
        }
    }

    _networkRequests.clear();
    _resources.clear();
}

void CommunicationResourceGateway::addResourceUrl(QUrl url) {
    DLog("-tmp- add resource url: ") << url;
    _resources.append(url);
}

void CommunicationResourceGateway::responseDataChunkAvailable(QByteArray resourceChunk, bool isBufferDownloadedResourceAndSendItWhenDownloadFinished) {
    BaseNetworkRequest* networkRequest = (BaseNetworkRequest*)QObject::sender();
    Q_EMIT resourceChunkReceivedForUrl(networkRequest->getRequestedURL(), resourceChunk, isBufferDownloadedResourceAndSendItWhenDownloadFinished);
}

void CommunicationResourceGateway::requestFinished() {
    BaseNetworkRequest* networkRequest = (BaseNetworkRequest*)QObject::sender();

    --_maxParallelRequestsCount;

    _networkRequests.removeOne(networkRequest);
    Q_EMIT resourceDownloadFinishedWithSuccess(networkRequest->getRequestedURL());

    networkRequest->disconnect();
//    AW_QOBJECT_SAFE_DELETE(networkRequest);
    AW_QOBJECT_SAFE_DELETE(networkRequest);

    // Try to load the next in the list
    startRequests();
}

void CommunicationResourceGateway::downloadProgress(int progress)
{
    BaseNetworkRequest* networkRequest = (BaseNetworkRequest*)QObject::sender();
    Q_EMIT downloadProgressForUrl(progress, networkRequest->getRequestedURL());
}

void CommunicationResourceGateway::requestFailed() {
    BaseNetworkRequest* networkRequest = (BaseNetworkRequest*)QObject::sender();

    Q_EMIT resourceDownloadFailedForUrl(networkRequest->getRequestedURL());

    --_maxParallelRequestsCount;

    _networkRequests.removeOne(networkRequest);

    networkRequest->disconnect();
//    AW_QOBJECT_SAFE_DELETE(networkRequest);
    AW_QOBJECT_SAFE_DELETE(networkRequest);

    // Try to load the next in the list
    startRequests();
}

void CommunicationResourceGateway::startRequests() {
    if (_resources.size() <= 0 &&
        _networkRequests.size() <= 0) {
        Q_EMIT finishedWithAllRequests();
        return;
    }

    if(_gatewayDelegate == NULL) {
        WLog("No gateway delegate defined");
        return;
    }

    while (_networkRequests.size() < _maxParallelRequestsCount &&
           _resources.size() > 0) {
        ++_maxParallelRequestsCount;

        QUrl resourceUrl = _resources.last();
        _resources.removeLast();

        // Setup the request
        QNetworkRequest::CacheLoadControl cacheControl = QNetworkRequest::AlwaysNetwork;
        NetworkRequestCacheDelegate *requestCacheDelegate = NULL;
        if(_gatewayCacheDelegate != NULL) {
            cacheControl = _gatewayCacheDelegate->getCacheControlForResourceUrl(resourceUrl);
            requestCacheDelegate = _gatewayCacheDelegate->getRequestCacheDelegate();
        }

        BaseNetworkRequest* networkRequest = _gatewayDelegate->createResourceDownloadRequest(BaseNetworkRequest::BaseCommunicationRequestTypeGet, resourceUrl, cacheControl, 10000, requestCacheDelegate);

        connect(networkRequest, SIGNAL(responseDataChunkAvailable(QByteArray,bool)), this, SLOT(responseDataChunkAvailable(QByteArray,bool)));
        connect(networkRequest, SIGNAL(requestProgress(int)), this, SLOT(downloadProgress(int)));
        connect(networkRequest, SIGNAL(failedToSendRequest()), this, SLOT(requestFailed()));
        connect(networkRequest, SIGNAL(requestTimedOut()), this, SLOT(requestFailed()));
        connect(networkRequest, SIGNAL(finished()), this, SLOT(requestFinished()));

        // Add it to the list
        _networkRequests.append(networkRequest);
        networkRequest->startThisRequest();
    }
}


} // namespace Communication
} // namespace Common
} // namespace AW
