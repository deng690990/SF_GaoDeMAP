//
//  AMapNaviDriveManager.h
//  AMapNaviKit
//
//  Created by 刘博 on 16/1/12.
//  Copyright © 2016年 AutoNavi. All rights reserved.
//

#import "AMapNaviBaseManager.h"
#import "AMapNaviDriveDataRepresentable.h"

NS_ASSUME_NONNULL_BEGIN

@protocol AMapNaviDriveManagerDelegate;

#pragma mark - AMapNaviDriveManager

/// 驾车导航管理类
@interface AMapNaviDriveManager : AMapNaviBaseManager

#pragma mark - Delegate

/**
 *  实现了 AMapNaviDriveManagerDelegate 协议的类指针
 */
@property (nonatomic, weak) id<AMapNaviDriveManagerDelegate> delegate;

#pragma mark - Data Representative

/**
 *  增加用于展示导航数据的DataRepresentative
 *
 *  注意:该方法不会增加实例对象的引用计数(Weak Reference)
 *
 *  @param aRepresentative 实现了 AMapNaviDriveDataRepresentable 协议的实例
 */
- (void)addDataRepresentative:(id<AMapNaviDriveDataRepresentable>)aRepresentative;

/**
 *  移除用于展示导航数据的DataRepresentative
 *
 *  @param aRepresentative 实现了 AMapNaviDriveDataRepresentable 协议的实例
 */
- (void)removeDataRepresentative:(id<AMapNaviDriveDataRepresentable>)aRepresentative;

#pragma mark - Navi Route

/**
 *  当前导航路径的ID
 */
@property (nonatomic, readonly) NSInteger naviRouteID;

/**
 *  当前导航路径的信息,参考 AMapNaviRoute 类.
 */
@property (nonatomic, readonly, nullable) AMapNaviRoute *naviRoute;

/**
 *  多路径规划时的所有路径ID,路径ID为NSInteger类型.
 */
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *naviRouteIDs;

/**
 *  多路径规划时的所有路径信息,参考 AMapNaviRoute 类.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSNumber *, AMapNaviRoute *> *naviRoutes;

/**
 *  多路径规划时选择路径
 *
 *  注意:该方法仅限于在开始导航前使用,开始导航后该方法无效.
 *
 *  @param routeID 路径ID
 *  @return 是否选择路径成功
 */
- (BOOL)selectNaviRouteWithRouteID:(NSInteger)routeID;

#pragma mark - Options

/**
 *  是否播报摄像头信息,默认YES.
 */
@property (nonatomic, assign) BOOL updateCameraInfo;

/**
 *  是否播报交通信息,默认YES(需要联网).
 */
@property (nonatomic, assign) BOOL updateTrafficInfo;

/**
 *  偏航时是否重新计算路径,默认YES(需要联网).
 */
@property (nonatomic, assign) BOOL isRecalculateRouteForYaw;

/**
 *  前方拥堵时是否重新计算路径,默认YES(需要联网).
 */
@property (nonatomic, assign) BOOL isRecalculateRouteForTrafficJam;

/**
 *  智能播报模式,默认为AMapNaviDetectedModeNone(需要联网).
 *
 *  智能播报适用于不设置目的驾车过程中,播报电子眼、特殊道路设施等信息
 *
 *  巡航信息参考 AMapNaviCruiseInfo , AMapNaviTrafficFacilityInfo 类及相关回调
 */
@property (nonatomic, assign) AMapNaviDetectedMode detectedMode;

#pragma mark - Calculate Route

/// 以下算路方法需要高德坐标(GCJ02)

/**
 *  不带起点的驾车路径规划
 *
 *  @param endPoints    终点坐标.终点列表的尾点为实际导航终点.
 *  @param wayPoints    途经点坐标,最多支持16个途经点.
 *  @param strategy     路径的计算策略
 *  @return 规划路径是否成功
 */
- (BOOL)calculateDriveRouteWithEndPoints:(NSArray<AMapNaviPoint *> *)endPoints
                               wayPoints:(nullable NSArray<AMapNaviPoint *> *)wayPoints
                         drivingStrategy:(AMapNaviDrivingStrategy)strategy;

/**
 *  带起点的驾车路径规划
 *
 *  @param startPoints  起点坐标.起点列表的尾点为实际导航起点,其他坐标点为辅助信息,带有方向性,可有效避免算路到马路的另一侧.
 *  @param endPoints    终点坐标.终点列表的尾点为实际导航终点,其他坐标点为辅助信息,带有方向性,可有效避免算路到马路的另一侧.
 *  @param wayPoints    途经点坐标,最多支持16个途经点.
 *  @param strategy     路径的计算策略
 *  @return 规划路径是否成功
 */
- (BOOL)calculateDriveRouteWithStartPoints:(NSArray<AMapNaviPoint *> *)startPoints
                                 endPoints:(NSArray<AMapNaviPoint *> *)endPoints
                                 wayPoints:(nullable NSArray<AMapNaviPoint *> *)wayPoints
                           drivingStrategy:(AMapNaviDrivingStrategy)strategy;

/**
 *  导航过程中重新规划路径(起点为当前位置,途经点和终点位置不变)
 *
 *  @param strategy 路径的计算策略
 *  @return 规划路径是否成功
 */
- (BOOL)recalculateDriveRouteWithDrivingStrategy:(AMapNaviDrivingStrategy)strategy;

#pragma mark - Manual

/**
 *  设置车牌信息
 *
 *  @param province 车牌省份缩写，例如：@"京"
 *  @param number 除省份及标点之外，车牌的字母和数字，例如：@"NH1N11"
 */
- (void)setVehicleProvince:(NSString *)province number:(NSString *)number;

/**
 *  设置播报模式,默认新手详细播报(AMapNaviBroadcastModeDetailed)
 *  @return 是否成功
 */
- (BOOL)setBroadcastMode:(AMapNaviBroadcastMode)mode;

/**
 *  手动刷新路况信息,调用后会刷新路况光柱.(SDK每四分钟自动刷新一次,但限制两次刷新的最小时间间隔为一分钟)
 */
- (void)refreshTrafficStatusesManual;

#pragma mark - Traffic Status

/**
 *  获取某一范围内的路况光柱信息
 *
 *  @param startPosition 光柱范围在路径中的起始位置,取值范围[0, routeLength)
 *  @param distance 光柱范围的距离,startPosition + distance 和的取值范围(0, routelength]
 *  @return 该范围内路况信息数组,可用于绘制光柱,参考 AMapNaviTrafficStatus 类.
 */
- (nullable NSArray<AMapNaviTrafficStatus *> *)getTrafficStatusesWithStartPosition:(int)startPosition distance:(int)distance;

@end

#pragma mark - AMapNaviDriveManagerDelegate

@protocol AMapNaviDriveManagerDelegate <NSObject>
@optional

/**
 *  发生错误时,会调用代理的此方法
 *
 *  @param error 错误信息
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager error:(NSError *)error;

/**
 *  驾车路径规划成功后的回调函数
 */
- (void)driveManagerOnCalculateRouteSuccess:(AMapNaviDriveManager *)driveManager;

/**
 *  驾车路径规划失败后的回调函数
 *
 *  @param error 错误信息,error.code参照AMapNaviCalcRouteState
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager onCalculateRouteFailure:(NSError *)error;

/**
 *  启动导航后回调函数
 *
 *  @param naviMode 导航类型，参考AMapNaviMode
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager didStartNavi:(AMapNaviMode)naviMode;

/**
 *  出现偏航需要重新计算路径时的回调函数
 */
- (void)driveManagerNeedRecalculateRouteForYaw:(AMapNaviDriveManager *)driveManager;

/**
 *  前方遇到拥堵需要重新计算路径时的回调函数
 */
- (void)driveManagerNeedRecalculateRouteForTrafficJam:(AMapNaviDriveManager *)driveManager;

/**
 *  导航到达某个途经点的回调函数
 *
 *  @param wayPointIndex 到达途径点的编号，标号从1开始
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager onArrivedWayPoint:(int)wayPointIndex;

/**
 *  导航播报信息回调函数
 *
 *  @param soundString 播报文字
 *  @param soundStringType 播报类型,参考AMapNaviSoundType
 */
- (void)driveManager:(AMapNaviDriveManager *)driveManager playNaviSoundString:(NSString *)soundString soundStringType:(AMapNaviSoundType)soundStringType;

/**
 *  模拟导航到达目的地停止导航后的回调函数
 */
- (void)driveManagerDidEndEmulatorNavi:(AMapNaviDriveManager *)driveManager;

/**
 *  导航到达目的地后的回调函数
 */
- (void)driveManagerOnArrivedDestination:(AMapNaviDriveManager *)driveManager;

@end

NS_ASSUME_NONNULL_END
