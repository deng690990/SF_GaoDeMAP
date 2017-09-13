//
//  AMapNaviRideManager.h
//  AMapNaviKit
//
//  Created by liubo on 9/19/16.
//  Copyright © 2016 AutoNavi. All rights reserved.
//

#import "AMapNaviBaseManager.h"
#import "AMapNaviRideDataRepresentable.h"

NS_ASSUME_NONNULL_BEGIN

@protocol AMapNaviRideManagerDelegate;

#pragma mark - AMapNaviRideManager

/// 骑行导航管理类
@interface AMapNaviRideManager : AMapNaviBaseManager

#pragma mark - Delegate

/**
 *  实现了 AMapNaviRideManagerDelegate 协议的类指针
 */
@property (nonatomic, weak) id<AMapNaviRideManagerDelegate> delegate;

#pragma mark - Data Representative

/**
 *  增加用于展示导航数据的DataRepresentative
 *
 *  注意:该方法不会增加实例对象的引用计数(Weak Reference)
 *
 *  @param aRepresentative 实现了 AMapNaviRideDataRepresentable 协议的实例
 */
- (void)addDataRepresentative:(id<AMapNaviRideDataRepresentable>)aRepresentative;

/**
 *  移除用于展示导航数据的DataRepresentative
 *
 *  @param aRepresentative 实现了 AMapNaviRideDataRepresentable 协议的实例
 */
- (void)removeDataRepresentative:(id<AMapNaviRideDataRepresentable>)aRepresentative;

#pragma mark - Navi Route

/**
 *  当前导航路径的ID
 */
@property (nonatomic, readonly) NSInteger naviRouteID;

/**
 *  当前导航路径的信息,参考 AMapNaviRoute 类.
 */
@property (nonatomic, readonly, nullable) AMapNaviRoute *naviRoute;

#pragma mark - Options

/**
 *  偏航时是否重新计算路径,默认YES(需要联网).
 */
@property (nonatomic, assign) BOOL isRecalculateRouteForYaw;

#pragma mark - Calculate Route

///以下算路方法需要高德坐标(GCJ02)

/**
 *  不带起点的骑行路径规划
 *
 *  @param endPoint 终点坐标.
 *  @return 规划路径是否成功
 */
- (BOOL)calculateRideRouteWithEndPoint:(AMapNaviPoint *)endPoint;

/**
 *  带起点的骑行路径规划
 *
 *  @param startPoint   起点坐标.
 *  @param endPoint     终点坐标.
 *  @return 规划路径是否成功
 */
- (BOOL)calculateRideRouteWithStartPoint:(AMapNaviPoint *)startPoint
                                endPoint:(AMapNaviPoint *)endPoint;

/**
 *  导航过程中重新规划路径(起点为当前位置,终点位置不变)
 *
 *  @return 规划路径是否成功
 */
- (BOOL)recalculateRideRoute;

@end

#pragma mark - AMapNaviRideManagerDelegate

@protocol AMapNaviRideManagerDelegate <NSObject>
@optional

/**
 *  发生错误时,会调用代理的此方法
 *
 *  @param error 错误信息
 */
- (void)rideManager:(AMapNaviRideManager *)rideManager error:(NSError *)error;

/**
 *  骑行路径规划成功后的回调函数
 */
- (void)rideManagerOnCalculateRouteSuccess:(AMapNaviRideManager *)rideManager;

/**
 *  骑行路径规划失败后的回调函数
 *
 *  @param error 错误信息,error.code参照AMapNaviCalcRouteState
 */
- (void)rideManager:(AMapNaviRideManager *)rideManager onCalculateRouteFailure:(NSError *)error;

/**
 *  启动导航后回调函数
 *
 *  @param naviMode 导航类型，参考AMapNaviMode
 */
- (void)rideManager:(AMapNaviRideManager *)rideManager didStartNavi:(AMapNaviMode)naviMode;

/**
 *  出现偏航需要重新计算路径时的回调函数
 */
- (void)rideManagerNeedRecalculateRouteForYaw:(AMapNaviRideManager *)rideManager;

/**
 *  导航播报信息回调函数
 *
 *  @param soundString 播报文字
 *  @param soundStringType 播报类型,参考AMapNaviSoundType
 */
- (void)rideManager:(AMapNaviRideManager *)rideManager playNaviSoundString:(NSString *)soundString soundStringType:(AMapNaviSoundType)soundStringType;

/**
 *  模拟导航到达目的地停止导航后的回调函数
 */
- (void)rideManagerDidEndEmulatorNavi:(AMapNaviRideManager *)rideManager;

/**
 *  导航到达目的地后的回调函数
 */
- (void)rideManagerOnArrivedDestination:(AMapNaviRideManager *)rideManager;

@end

NS_ASSUME_NONNULL_END
