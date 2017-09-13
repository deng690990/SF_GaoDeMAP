//
//  AMapGeoFenceRegionObj.h
//  AMapLocationKit
//
//  Created by hanxiaoming on 16/12/5.
//  Copyright © 2016年 Amap. All rights reserved.
//

#import "AMapLocationCommonObj.h"


///AMapGeoFence Region State
typedef NS_ENUM(NSInteger, AMapGeoFenceRegionStatus)
{
    AMapGeoFenceRegionStatusUnknown  = 0,       ///< 未知
    AMapGeoFenceRegionStatusInside   = 1,       ///< 在范围内
    AMapGeoFenceRegionStatusOutside  = 2,       ///< 在范围外
    AMapGeoFenceRegionStatusStayed   = 3,       ///< 停留(在范围内超过10分钟)
};

#pragma mark - AMapGeoFenceRegion


///地理围栏基类，不可直接使用。（since 2.3.0）
@interface AMapGeoFenceRegion : NSObject<NSCopying>


///AMapGeoFenceRegion的唯一标识符
@property (nonatomic, copy, readonly) NSString *identifier;


///用户自定义ID，可为nil。
@property (nonatomic, copy, readonly) NSString *customID;


///坐标点和围栏的关系，比如用户的位置和围栏的关系
@property (nonatomic, assign) AMapGeoFenceRegionStatus fenceStatus;

@end


#pragma mark - AMapLocationCircleRegion


///圆形地理围栏（since 2.3.0）
@interface AMapGeoFenceCircleRegion : AMapGeoFenceRegion


///中心点的经纬度坐标
@property (nonatomic, readonly) CLLocationCoordinate2D center;


///半径，单位：米
@property (nonatomic, readonly) CLLocationDistance radius;

@end


#pragma mark -AMapGeoFencePolygonRegion


///多边形地理围栏（since 2.3.0）
@interface AMapGeoFencePolygonRegion : AMapGeoFenceRegion


///经纬度坐标点数据
@property (nonatomic, readonly) CLLocationCoordinate2D *coordinates;


///经纬度坐标点的个数
@property (nonatomic, readonly) NSInteger count;


@end


#pragma mark -AMapGeoFencePOIRegion


///兴趣点（POI）地理围栏（since 2.3.0）
@interface AMapGeoFencePOIRegion : AMapGeoFenceCircleRegion


///POI信息
@property (nonatomic, strong, readonly) AMapLocationPOIItem *POIItem;


@end


#pragma mark -AMapGeoFenceDistrictRegion


///行政区划地理围栏（since 2.3.0）
@interface AMapGeoFenceDistrictRegion : AMapGeoFenceRegion


///行政区域信息
@property (nonatomic, strong, readonly) AMapLocationDistrictItem *districtItem;


///行政区域轮廓坐标点，每个行政区可能有多个模块,每个模块的坐标点数组由AMapLocationPoint构成
@property (nonatomic, copy, readonly) NSArray <NSArray<AMapLocationPoint *> *> *polylinePoints;


@end
