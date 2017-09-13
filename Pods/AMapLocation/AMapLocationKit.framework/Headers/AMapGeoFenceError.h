//
//  AMapGeoFenceError.h
//  AMapLocationKit
//
//  Created by eidan on 16/12/15.
//  Copyright © 2016年 Amap. All rights reserved.
//

#ifndef AMapGeoFenceError_h
#define AMapGeoFenceError_h


///AMapGeoFence errorDomain
extern NSString * const AMapGeoFenceErrorDomain;

///地理围栏错误码
typedef NS_ENUM(NSInteger, AMapGeoFenceErrorCode) {
    AMapGeoFenceErrorUnknown = 1,                    ///< 未知错误
    AMapGeoFenceErrorInvalidParameter = 2,           ///< 参数错误
    AMapGeoFenceErrorFailureConnection = 3,          ///< 网络连接异常
    AMapGeoFenceErrorFailureAuth  = 4,               ///< 鉴权失败
    AMapGeoFenceErrorNoValidFence = 5,               ///< 无可用围栏
    AMapGeoFenceErroFailureLocating = 6,             ///< 定位错误
};

#endif /* AMapGeoFenceError_h */
