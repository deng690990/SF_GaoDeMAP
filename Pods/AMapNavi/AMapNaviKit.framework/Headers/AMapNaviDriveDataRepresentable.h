//
//  AMapNaviDriveDataRepresentable.h
//  AMapNaviKit
//
//  Created by 刘博 on 16/1/13.
//  Copyright © 2016年 AutoNavi. All rights reserved.
//

#import "AMapNaviCommonObj.h"

NS_ASSUME_NONNULL_BEGIN

@class AMapNaviInfo;
@class AMapNaviRoute;
@class AMapNaviLocation;
@class AMapNaviStatisticsInfo;
@class AMapNaviDriveManager;

/**
 *  AMapNaviDriveDataRepresentable协议
 *  
 *  实例对象可以通过实现该协议,并将其通过 AMapNaviDriveManager 的addDataRepresentative:方法进行注册,便可获取导航过程中的导航数据更新.
 *
 *  可以根据不同需求,选取使用特定的数据进行导航界面自定义. AMapNaviDriveView 即通过该协议实现导航过程展示.
 *
 *  也可以依据导航数据的更新进行其他的逻辑处理.
 */
@protocol AMapNaviDriveDataRepresentable <NSObject>
@optional

/**
 *  导航模式更新回调
 *
 *  @param naviMode 导航模式,参考AMapNaviMode
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateNaviMode:(AMapNaviMode)naviMode;

/**
 *  路径ID更新回调
 *
 *  @param naviRouteID 导航路径ID
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateNaviRouteID:(NSInteger)naviRouteID;

/**
 *  路径信息更新回调
 *
 *  @param naviRoute 路径信息,参考 AMapNaviRoute 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateNaviRoute:(nullable AMapNaviRoute *)naviRoute;

/**
 *  导航信息更新回调
 *
 *  @param naviInfo 导航信息,参考 AMapNaviInfo 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateNaviInfo:(nullable AMapNaviInfo *)naviInfo;

/**
 *  自车位置更新回调
 *
 *  @param naviLocation 自车位置信息,参考 AMapNaviLocation 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateNaviLocation:(nullable AMapNaviLocation *)naviLocation;

/**
 *  需要显示路口放大图时的回调
 *
 *  @param crossImage 路口放大图Image(size:400*400)
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager showCrossImage:(UIImage *)crossImage;

/**
 *  需要隐藏路口放大图时的回调
 */
- (void)driveManagerHideCrossImage:(AMapNaviDriveManager *)driveManager;

/**
 *  需要显示车道信息时的回调
 *
 *  可通过 UIImage *CreateLaneInfoImageWithLaneInfo(NSString *laneBackInfo, NSString *laneSelectInfo); 方法创建车道信息图片
 *
 *  0-直行; 1-左转; 2-直行和左转; 3-右转;
 *  4-直行和右转; 5-左转掉头; 6-左转和右转; 7-直行和左转和右转;
 *  8-右转掉头; 9-直行和左转掉头; a-直行和右转掉头; b-左转和左转掉头;
 *  c-右转和右转掉头; d-左侧变宽直行; e-左侧变宽左转和左转掉头; f-保留;
 *
 *  @param laneBackInfo 车道背景信息，例如：@"1|0|0|0|3|f|f|f"，表示当前道路有5个车道，分别为"左转-直行-直行-直行-右转"
 *  @param laneSelectInfo 车道前景信息，例如：@"f|0|0|0|f|f|f|f"，表示选择当前道路的2、3、4三个直行车道
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager showLaneBackInfo:(NSString *)laneBackInfo laneSelectInfo:(NSString *)laneSelectInfo;

/**
 *  需要隐藏车道信息时的回调
 */
- (void)driveManagerHideLaneInfo:(AMapNaviDriveManager *)driveManager;

/**
 *  路况光柱信息更新回调
 *
 *  @param trafficStatus 路况光柱信息数组,参考 AMapNaviTrafficStatus 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateTrafficStatus:(nullable NSArray<AMapNaviTrafficStatus *> *)trafficStatus;

/**
 *  巡航道路设施信息更新回调
 *
 *  该更新回调只有在detectedMode开启后有效
 *
 *  @param trafficFacilities 道路设施信息数组,参考 AMapNaviTrafficFacilityInfo 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateTrafficFacilities:(nullable NSArray<AMapNaviTrafficFacilityInfo *> *)trafficFacilities;

/**
 *  巡航信息更新回调
 *
 *  该更新回调只有在detectedMode开启后有效
 *
 *  @param cruiseInfo 巡航信息,参考 AMapNaviCruiseInfo 类
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager updateCruiseInfo:(nullable AMapNaviCruiseInfo *)cruiseInfo;

@end

NS_ASSUME_NONNULL_END
