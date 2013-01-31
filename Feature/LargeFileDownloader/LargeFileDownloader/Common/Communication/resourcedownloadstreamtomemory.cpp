#include "resourcedownloadstreamtomemory.h"

#include "Common/Communication/resourcedownloadnetworkrequest.h"

namespace AW {
namespace Common {
namespace Communication {

ResourceDownloadStreamToMemory::ResourceDownloadStreamToMemory(CommunicationResourceGateway::CommunicationResourceGatewayCacheDelegate *commResourceGatewayCacheDelegate, unsigned int maxParallelRequestsCount, QObject *parent) :
    QObject(parent)
{    
    _commResourceGateway = new CommunicationResourceGateway(this, commResourceGatewayCacheDelegate, maxParallelRequestsCount, this);
    connect(_commResourceGateway, SIGNAL(downloadProgressForUrl(int,QUrl)), this, SLOT(_downloadProgressForUrl(int,QUrl)));
    connect(_commResourceGateway, SIGNAL(resourceDownloadFailedForUrl(QUrl)), this, SLOT(_resourceDownloadFailedForUrl(QUrl)));
    connect(_commResourceGateway, SIGNAL(resourceChunkReceivedForUrl(QUrl,QByteArray,bool)), this, SLOT(_resourceChunkReceivedForUrl(QUrl,QByteArray,bool)));
    connect(_commResourceGateway, SIGNAL(resourceDownloadFinishedWithSuccess(QUrl)), this, SLOT(_finishedResourceDownloading(QUrl)));
    connect(_commResourceGateway, SIGNAL(finishedWithAllRequests()), this, SLOT(_allNetworkRequestsFinished()));
}


void ResourceDownloadStreamToMemory::addResourceDownloadRequest(QUrl url)
{
    _commResourceGateway->addResourceUrl(url);
}

void ResourceDownloadStreamToMemory::startDownloadingResources()
{
    _commResourceGateway->startRequests();
}

// --------------------------------------------
// resource network request handling

void ResourceDownloadStreamToMemory::_downloadProgressForUrl(int percent, QUrl url)
{
    Q_EMIT resourceDownloadProgressForUrl(percent, url);
}

void ResourceDownloadStreamToMemory::_resourceDownloadFailedForUrl(QUrl url)
{
    WLog("resource download FAILED: ") << url;
    Q_EMIT resourceDownloadFailedForUrl(url);
}

void ResourceDownloadStreamToMemory::_resourceChunkReceivedForUrl(QUrl url, QByteArray resourceChunk, bool isBufferDownloadedResourceAndSendItWhenDownloadFinished)
{
    if(!isBufferDownloadedResourceAndSendItWhenDownloadFinished) {
        WLog("isBufferDownloadedResourceAndSendItWhenDownloadFinished is FALSE - it should be TRUE!");

        WLog("Chunk is not the whole resource - it's not stored in memory in it's whole!");
        Q_EMIT resourceDownloadFailedForUrl(url);
        return;
    }

    DLog("Resource retrieved:") << url;
    Q_EMIT resourceDownloadFinishedWithSuccess(url, resourceChunk);
}

void ResourceDownloadStreamToMemory::_finishedResourceDownloading(QUrl url)
{
    DLog("Finished resource downloading:") << url;
}

void ResourceDownloadStreamToMemory::_allNetworkRequestsFinished()
{
    DLog("Finished with all resource downloading");
    Q_EMIT finishedWithAllResourceDownloads();
}


// --------------------------------------------
// CommunicationResourceGatewayDelegate

BaseNetworkRequest *ResourceDownloadStreamToMemory::createResourceDownloadRequest(BaseNetworkRequest::BaseCommunicationRequestType requestType, QUrl requestUrl, QNetworkRequest::CacheLoadControl cacheControl, int timeoutInterval, NetworkRequestCacheDelegate *requestCacheDelegate)
{
    return new ResourceDownloadNetworkRequest(requestType, requestUrl, cacheControl, timeoutInterval, true, requestCacheDelegate);
}

} // namespace Communication
} // namespace Common
} // namespace AW
