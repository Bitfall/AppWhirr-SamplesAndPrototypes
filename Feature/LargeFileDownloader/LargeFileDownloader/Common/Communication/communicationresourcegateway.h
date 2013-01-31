#ifndef COMMUNICATIONRESOURCEGATEWAY_H
#define COMMUNICATIONRESOURCEGATEWAY_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include "Common/Communication/basenetworkrequest.h"
#include <QUrl>

namespace AW {
namespace Common {
namespace Communication {

class CommunicationResourceGateway : public QObject
{
    Q_OBJECT

public:
    class CommunicationResourceGatewayDelegate {
    public:
        virtual ~CommunicationResourceGatewayDelegate() {}

        /*! Create a network-request by the parameters

            @param cachePolicy : it's the cache-control given by CommunicationResourceGatewayCacheDelegate's \a getCacheControlForResourceUrl()
            @param timeoutInterval : in milliseconds
            @param requestCacheDelegate : cache-delegate for the request. Given by CommunicationResourceGatewayCacheDelegate's \a getRequestCacheDelegate()
        */
        virtual BaseNetworkRequest *createResourceDownloadRequest(BaseNetworkRequest::BaseCommunicationRequestType requestType,
                                                                  QUrl requestUrl,
                                                                  QNetworkRequest::CacheLoadControl cacheControl,
                                                                  int timeoutInterval,
                                                                  NetworkRequestCacheDelegate *requestCacheDelegate) = 0;
    };

    class CommunicationResourceGatewayCacheDelegate {
    public:
        virtual ~CommunicationResourceGatewayCacheDelegate() {}

        virtual QNetworkRequest::CacheLoadControl getCacheControlForResourceUrl(QUrl url) = 0;
        /*! Cache delegate for a given resource request

            @return Return NULL (by default) if no cache delegate should be applied for the request
        */
        virtual NetworkRequestCacheDelegate *getRequestCacheDelegate() { return NULL; }
    };

public:
    /*! Resource gateway

        @param gatewayCacheDelegate : if NULL no cache will be applied
    */
    explicit CommunicationResourceGateway(CommunicationResourceGatewayDelegate *gatewayDelegate, CommunicationResourceGatewayCacheDelegate *gatewayCacheDelegate = NULL, unsigned int maxParallelRequestsCount = 5, QObject *parent = 0);
    virtual ~CommunicationResourceGateway();

    /*! Adds a new resource URL to be loaded */
    /** After adding all the resources you should call the startRequests() method
        @warning It do not starts loading the resource.
      */
    void addResourceUrl(QUrl url);

    /*! Starts loading the requests */
    /**
      */
    void startRequests();

Q_SIGNALS:
    /*! Emits when a resource was retrieved*/
    /**
      */
    void resourceChunkReceivedForUrl(QUrl url, QByteArray resourceChunk, bool isBufferDownloadedResourceAndSendItWhenDownloadFinished);
    void resourceDownloadFailedForUrl(QUrl url);
    /*! Will be emitted when the given resource is 100% retrieved
    */
    void resourceDownloadFinishedWithSuccess(QUrl url);
    /*! Emits when all resources were retrieved */
    /** @warning You should only connect to this Q_SIGNAL, when all your resources is added to this class
      */
    void finishedWithAllRequests();

    void downloadProgressForUrl(int progress, QUrl url);

private Q_SLOTS:
    void requestFinished();
    void responseDataChunkAvailable(QByteArray response, bool isBufferDownloadedResourceAndSendItWhenDownloadFinished);
    void requestFailed();
    void downloadProgress(int progress);

private:
    QList<QUrl>                 _resources;
    QList<BaseNetworkRequest*>  _networkRequests;
    unsigned int                _maxParallelRequestsCount;

    CommunicationResourceGatewayDelegate *_gatewayDelegate;
    CommunicationResourceGatewayCacheDelegate *_gatewayCacheDelegate;
};

} // namespace Communication
} // namespace Common
} // namespace AW

#endif // COMMUNICATIONRESOURCEGATEWAY_H
