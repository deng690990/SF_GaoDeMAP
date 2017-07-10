//
//  AMapLocationManager.h
//  AMapLocationKit
//
//  Created by AutoNavi on 15/10/22.
//  Copyright © 2015年 Amap. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AMapLocationCommonObj.h"
#import "AMapLocationRegionObj.h"

/**
 *  @brief AMapLocatingCompletionBlock 单次定位返回Block
 *  @param location 定位信息
 *  @param regeocode 逆地理信息
 *  @param error 错误信息，参考 AMapLocationErrorCode
 */
typedef void (^AMapLocatingCompletionBlock)(CLLocation *location, AMapLocationReGeocode *regeocode, NSError *error);

@protocol AMapLocationManagerDelegate;

#pragma mark - AMapLocationManager

///AMapLocationManager类。初始化之前请设置 AMapServices 中的apikey(例如：[AMapServices sharedServices].apiKey = @"您的key")，否则将无法正常使用服务.
@interface AMapLocationManager : NSObject

///实现了 AMapLocationManagerDelegate 协议的类指针。
@property (nonatomic, weak) id<AMapLocationManagerDelegate> delegate;

///设定定位的最小更新距离。单位米，默认为 kCLDistanceFilterNone，表示只要检测到设备位置发生变化就会更新位置信息。
@property(nonatomic, assign) CLLocationDistance distanceFilter;

///设定期望的定位精度。单位米，默认为 kCLLocationAccuracyBest。定位服务会尽可能去获取满足desiredAccuracy的定位结果，但不保证一定会得到满足期望的结果。 \n注意：设置为kCLLocationAccuracyBest或kCLLocationAccuracyBestForNavigation时，单次定位会在达到locationTimeout设定的时间后，将时间内获取到的最高精度的定位结果返回。
@property(nonatomic, assign) CLLocationAccuracy desiredAccuracy;

///指定定位是否会被系统自动暂停。默认为NO。
@property(nonatomic, assign) BOOL pausesLocationUpdatesAutomatically;

///是否允许后台定位。默认为NO。只在iOS 9.0及之后起作用。设置为YES的时候必须保证 Background Modes 中的 Location updates 处于选中状态，否则会抛出异常。由于iOS系统限制，需要在定位未开始之前或定位停止之后，修改该属性的值才会有效果。
@property(nonatomic, assign) BOOL allowsBackgroundLocationUpdates;

///指定单次定位超时时间,默认为10s。最小值是2s。注意单次定位请求前设置。注意: 单次定位超时时间从确定了定位权限(非kCLAuthorizationStatusNotDetermined状态)后开始计算。
@property(nonatomic, assign) NSInteger locationTimeout;

///指定单次定位逆地理超时时间,默认为5s。最小值是2s。注意单次定位请求前设置。
@property(nonatomic, assign) NSInteger reGeocodeTimeout;

///连续定位是否返回逆地理信息，默认NO。
@property (nonatomic, assign) BOOL locatingWithReGeocode;

///获取被监控的region集合。
@property (nonatomic, readonly, copy) NSSet *monitoredRegions;

///检测是否存在虚拟定位风险，默认为NO，不检测。 \n注意:设置为YES时，单次定位通过 AMapLocatingCompletionBlock 的error给出虚拟定位风险提示；连续定位通过 amapLocationManager:didFailWithError: 方法的error给出虚拟定位风险提示。error格式为error.domain==AMapLocationErrorDomain; error.code==AMapLocationErrorRiskOfFakeLocation;
@property (nonatomic, assign) BOOL detectRiskOfFakeLocation;

/**
 *  @brief 单次定位。如果当前正在连续定位，调用此方法将会失败，返回NO。\n该方法将会根据设定的 desiredAccuracy 去获取定位信息。如果获取的定位信息精确度低于 desiredAccuracy ，将会持续的等待定位信息，直到超时后通过completionBlock返回精度最高的定位信息。\n可以通过 stopUpdatingLocation 方法去取消正在进行的单次定位请求。
 *  @param withReGeocode 是否带有逆地理信息(获取逆地理信息需要联网)
 *  @param completionBlock 单次定位完成后的Block
 *  @return 是否成功添加单次定位Request
 */
- (BOOL)requestLocationWithReGeocode:(BOOL)withReGeocode completionBlock:(AMapLocatingCompletionBlock)completionBlock;

/**
 *  @brief 开始连续定位。调用此方法会cancel掉所有的单次定位请求。
 */
- (void)startUpdatingLocation;

/**
 *  @brief 停止连续定位。调用此方法会cancel掉所有的单次定位请求，可以用来取消单次定位。
 */
- (void)stopUpdatingLocation;

/**
 *  @brief 开始监控指定的region。如果已经存在相同identifier的region，则之前的region将会被移除。对 AMapLocationCircleRegion 类实例，将会优先监控radius小的region。
 *  @param region 要被监控的范围
 */
- (void)startMonitoringForRegion:(AMapLocationRegion *)region;

/**
 *  @brief 停止监控指定的region
 *  @param region 要停止监控的范围
 */
- (void)stopMonitoringForRegion:(AMapLocationRegion *)region;

/**
 *  @brief 查询一个region的当前状态。查询结果通过amapLocationManager:didDetermineState:forRegion:回调返回
 *  @param region 要查询的region
 */
- (void)requestStateForRegion:(AMapLocationRegion *)region;

@end

#pragma mark - AMapLocationManagerDelegate


///AMapLocationManagerDelegate 协议定义了发生错误时的错误回调方法，连续定位的回调方法等。
@protocol AMapLocationManagerDelegate <NSObject>

@optional

/**
 *  @brief 当定位发生错误时，会调用代理的此方法。
 *  @param manager 定位 AMapLocationManager 类。
 *  @param error 返回的错误，参考 CLError 。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didFailWithError:(NSError *)error;

/**
 *  @brief 连续定位回调函数.注意：本方法已被废弃，如果实现了amapLocationManager:didUpdateLocation:reGeocode:方法，则本方法将不会回调。
 *  @param manager 定位 AMapLocationManager 类。
 *  @param location 定位结果。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didUpdateLocation:(CLLocation *)location;

/**
 *  @brief 连续定位回调函数.注意：如果实现了本方法，则定位信息不会通过amapLocationManager:didUpdateLocation:方法回调。
 *  @param manager 定位 AMapLocationManager 类。
 *  @param location 定位结果。
 *  @param reGeocode 逆地理信息。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didUpdateLocation:(CLLocation *)location reGeocode:(AMapLocationReGeocode *)reGeocode;

/**
 *  @brief 定位权限状态改变时回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param status 定位权限状态。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status;

/**
 *  @brief 开始监控region回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param region 开始监控的region。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didStartMonitoringForRegion:(AMapLocationRegion *)region;

/**
 *  @brief 进入region回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param region 进入的region。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didEnterRegion:(AMapLocationRegion *)region;

/**
 *  @brief 离开region回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param region 离开的region。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didExitRegion:(AMapLocationRegion *)region;

/**
 *  @brief 查询region状态回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param state 查询的region的状态。
 *  @param region 查询的region。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager didDetermineState:(AMapLocationRegionState)state forRegion:(AMapLocationRegion *)region;

/**
 *  @brief 监控region失败回调函数
 *  @param manager 定位 AMapLocationManager 类。
 *  @param region 失败的region。
 *  @param error 错误信息，参考 AMapLocationErrorCode 。
 */
- (void)amapLocationManager:(AMapLocationManager *)manager monitoringDidFailForRegion:(AMapLocationRegion *)region withError:(NSError *)error;

@end
