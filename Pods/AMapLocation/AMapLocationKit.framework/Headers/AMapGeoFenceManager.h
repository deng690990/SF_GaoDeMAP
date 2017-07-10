//
//  AMapGeoFenceManager.h
//  AMapLocationKit
//
//  Created by hanxiaoming on 16/12/5.
//  Copyright © 2016年 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMapGeoFenceRegionObj.h"

// 以下类涉及的坐标需要使用高德坐标系坐标(GCJ02)

@protocol AMapGeoFenceManagerDelegate;

///地理围栏监听状态类型
typedef NS_OPTIONS(NSUInteger, AMapGeoFenceActiveAction)
{
    AMapGeoFenceActiveActionNone     = 0,       ///< 不进行监听
    AMapGeoFenceActiveActionInside   = 1 << 0,  ///< 在范围内
    AMapGeoFenceActiveActionOutside  = 1 << 1,  ///< 在范围外
    AMapGeoFenceActiveActionStayed   = 1 << 2,  ///< 停留(在范围内超过10分钟)
};


///地理围栏管理类（since 2.3.0）
@interface AMapGeoFenceManager : NSObject


///实现了 AMapGeoFenceManagerDelegate 协议的类指针。
@property (nonatomic, weak) id<AMapGeoFenceManagerDelegate> delegate;


///需要进行通知的行为，默认为AMapGeoFenceActiveActionInside。
@property (nonatomic, assign) AMapGeoFenceActiveAction activeAction;


///指定定位是否会被系统自动暂停。默认为NO。
@property (nonatomic, assign) BOOL pausesLocationUpdatesAutomatically;


///是否允许后台定位。默认为NO。只在iOS 9.0及之后起作用。设置为YES的时候必须保证 Background Modes 中的 Location updates 处于选中状态，否则会抛出异常。
@property (nonatomic, assign) BOOL allowsBackgroundLocationUpdates;

///检测是否存在虚拟定位风险，默认为NO，即不检测。 \n如果设置为YES，检测到风险后，会通过amapGeoFenceManager:didGeoFencesStatusChangedForRegion:customID:error: 的error给出风险提示，error的格式为error.domain==AMapGeoFenceErrorDomain; error.code==AMapGeoFenceErroFailureLocating; 
@property (nonatomic, assign) BOOL detectRiskOfFakeLocation;


/**
 * @brief 添加一个圆形围栏
 * @param center 围栏的中心点经纬度坐标
 * @param radius 围栏的半径，单位：米，要求大于0
 * @param customID 用户自定义ID，可选，SDK原值返回
 */
- (void)addCircleRegionForMonitoringWithCenter:(CLLocationCoordinate2D)center radius:(CLLocationDistance)radius customID:(NSString *)customID;


/**
 * @brief 根据经纬度坐标数据添加一个闭合的多边形围栏，点与点之间按顺序尾部相连, 第一个点与最后一个点相连
 * @param coordinates 经纬度坐标点数据,coordinates对应的内存会拷贝,调用者负责该内存的释放
 * @param count 经纬度坐标点的个数，不可小于3个
 * @param customID 用户自定义ID，可选，SDK原值返回
 */
- (void)addPolygonRegionForMonitoringWithCoordinates:(CLLocationCoordinate2D *)coordinates count:(NSInteger)count customID:(NSString *)customID;


/**
 * @brief 根据要查询的关键字，类型，城市等信息，添加一个或者多个POI地理围栏
 * @param keyword 要查询的关键字，多个关键字用“|”分割，必填，keyword和type两者至少必选其一
 * @param type 要查询的POI类型，多个类型用“|”分割，必填，keyword和type两者至少必选其一，具体分类编码和规则详见： http://lbs.amap.com/api/webservice/guide/api/search/#text
 * @param city 要查询的城市
 * @param size 要查询的数据的条数，(0,25]，传入<=0的值为10，传入大于25的值为25，默认10
 * @param customID 用户自定义ID，可选，SDK原值返回
 */
- (void)addKeywordPOIRegionForMonitoringWithKeyword:(NSString *)keyword POIType:(NSString *)type city:(NSString *)city size:(NSInteger)size customID:(NSString *)customID;


/**
 * @brief 根据要查询的点的经纬度，搜索半径等信息，添加一个或者多个POI围栏
 * @param locationPoint 点的经纬度坐标，必填
 * @param aroundRadius 查询半径，单位：米，(0,50000]，超出范围取3000，默认3000
 * @param keyword 要查询的关键字，多个关键字用“|”分割，可选
 * @param type 要查询的POI类型，多个类型用“|”分割，可选
 * @param size 要查询的数据的条数，(0,25]，传入<=0的值为10，传入大于25的值为25，默认10
 * @param customID 用户自定义ID，可选，SDK原值返回
 */
- (void)addAroundPOIRegionForMonitoringWithLocationPoint:(CLLocationCoordinate2D)locationPoint aroundRadius:(NSInteger)aroundRadius keyword:(NSString *)keyword POIType:(NSString *)type size:(NSInteger)size customID:(NSString *)customID;


/**
 * @brief 根据要查询的行政区域关键字，添加一个或者多个行政区域围栏
 * @param districtName 行政区域关键字，必填，只支持单个关键词语：行政区名称、citycode、adcode，规则详见： http://lbs.amap.com/api/webservice/guide/api/district/#district
 * @param customID 用户自定义ID，可选，SDK原值返回
 */
- (void)addDistrictRegionForMonitoringWithDistrictName:(NSString *)districtName customID:(NSString *)customID;


/**
 * @brief 根据customID获得指定的围栏，如果customID传nil，则返回全部围栏
 * @param customID 用户执行添加围栏函数时传入的customID
 * @return 获得的围栏构成的数组，如果没有结果，返回nil
 */
- (NSArray *)geoFenceRegionsWithCustomID:(NSString *)customID;


/**
 * @brief 移除指定围栏
 * @param region 要停止监控的围栏
 */
- (void)removeTheGeoFenceRegion:(AMapGeoFenceRegion *)region;


/**
 * @brief 移除指定customID的围栏
 * @param customID 用户执行添加围栏函数时传入的customID
 */
- (void)removeGeoFenceRegionsWithCustomID:(NSString *)customID;


/**
 * @brief 移除所有围栏
 */
- (void)removeAllGeoFenceRegions;


@end



///地理围栏代理协议（since 2.3.0）,该协议定义了获取地理围栏相关回调方法，包括添加、状态改变等。
@protocol AMapGeoFenceManagerDelegate <NSObject>

@optional


/**
 * @brief 添加地理围栏完成后的回调，成功与失败都会调用
 * @param manager 地理围栏管理类
 * @param regions 成功添加的一个或多个地理围栏构成的数组
 * @param customID 用户执行添加围栏函数时传入的customID
 * @param error 添加失败的错误信息
 */
- (void)amapGeoFenceManager:(AMapGeoFenceManager *)manager didAddRegionForMonitoringFinished:(NSArray <AMapGeoFenceRegion *> *)regions customID:(NSString *)customID error:(NSError *)error;


/**
 * @brief 地理围栏状态改变时回调，当围栏状态的值发生改变，定位失败都会调用
 * @param manager 地理围栏管理类
 * @param region 状态改变的地理围栏
 * @param customID 用户执行添加围栏函数时传入的customID
 * @param error 错误信息，如定位相关的错误
 */
- (void)amapGeoFenceManager:(AMapGeoFenceManager *)manager didGeoFencesStatusChangedForRegion:(AMapGeoFenceRegion *)region customID:(NSString *)customID error:(NSError *)error;

@end
