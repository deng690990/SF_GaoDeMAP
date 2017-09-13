//
//  AMapNaviCommonObj.h
//  AMapNaviKit
//
//  Created by AutoNavi on 14-7-1.
//  Copyright (c) 2014年 AutoNavi. All rights reserved.
//

#import <UIKit/UIKit.h>

/// AMapNavi的错误Domain
extern NSString * const AMapNaviErrorDomain;

/// AMapNavi的错误信息
typedef NS_ENUM(NSInteger, AMapNaviError)
{
    AMapNaviUnknowError = -1,                   //!< 未知错误
    AMapNaviErrorNoGPSPermission = -2,          //!< 没有GPS权限
};

/// 导航模式
typedef NS_ENUM(NSInteger, AMapNaviMode)
{
    AMapNaviModeNone = 0,                       //!< 没有开始导航
    AMapNaviModeGPS,                            //!< GPS导航
    AMapNaviModeEmulator,                       //!< 模拟导航
};

/// 导航界面跟随模式
typedef NS_ENUM(NSInteger, AMapNaviViewTrackingMode)
{
    AMapNaviViewTrackingModeMapNorth = 0,      //!< 0 地图朝北
    AMapNaviViewTrackingModeCarNorth,          //!< 1 车头朝北
};

/// 驾车路径规划策略
typedef NS_ENUM(NSInteger, AMapNaviDrivingStrategy)
{
    AMapNaviDrivingStrategySingleDefault = 0,                               //!< 0 单路径: 默认
    AMapNaviDrivingStrategySingleAvoidCost = 1,                             //!< 1 单路径: 避免收费
    AMapNaviDrivingStrategySinglePrioritiseDistance = 2,                    //!< 2 单路径: 距离优先
    AMapNaviDrivingStrategySingleAvoidExpressway = 3,                       //!< 3 单路径: 不走快速路
    AMapNaviDrivingStrategySingleAvoidCongestion = 4,                       //!< 4 单路径: 躲避拥堵
    AMapNaviDrivingStrategySingleAvoidHighway = 6,                          //!< 6 单路径: 不走高速
    AMapNaviDrivingStrategySingleAvoidHighwayAndCost = 7,                   //!< 7 单路径: 不走高速 & 避免收费
    AMapNaviDrivingStrategySingleAvoidCostAndCongestion = 8,                //!< 8 单路径: 避免收费 & 躲避拥堵
    AMapNaviDrivingStrategySingleAvoidHighwayAndCostAndCongestion = 9,      //!< 9 单路径: 不走高速 & 避免收费 & 躲避拥堵
    
    AMapNaviDrivingStrategyMultipleDefault = 10,                            //!< 10 多路径: 默认
    AMapNaviDrivingStrategyMultipleAvoidCongestion = 12,                    //!< 12 多路径: 躲避拥堵
    AMapNaviDrivingStrategyMultipleAvoidHighway = 13,                       //!< 13 多路径: 不走高速
    AMapNaviDrivingStrategyMultipleAvoidCost = 14,                          //!< 14 多路径: 避免收费
    AMapNaviDrivingStrategyMultipleAvoidHighwayAndCongestion = 15,          //!< 15 多路径: 不走高速 & 躲避拥堵
    AMapNaviDrivingStrategyMultipleAvoidHighwayAndCost = 16,                //!< 16 多路径: 不走高速 & 避免收费
    AMapNaviDrivingStrategyMultipleAvoidCostAndCongestion = 17,             //!< 17 多路径: 避免收费 & 躲避拥堵
    AMapNaviDrivingStrategyMultipleAvoidHighwayAndCostAndCongestion = 18,   //!< 18 多路径: 不走高速 & 避免收费 & 躲避拥堵
    AMapNaviDrivingStrategyMultiplePrioritiseHighway = 19,                  //!< 19 多路径: 高速优先
    AMapNaviDrivingStrategyMultiplePrioritiseHighwayAvoidCongestion = 20,   //!< 20 多路径: 高速优先 & 躲避拥堵
    
    /// Deprecated
    AMapNaviDrivingStrategyDefault __attribute__ ((deprecated("use AMapNaviDrivingStrategySingleDefault instead"))) = AMapNaviDrivingStrategySingleDefault ,
    AMapNaviDrivingStrategySaveMoney __attribute__ ((deprecated("use AMapNaviDrivingStrategySingleAvoidCost instead"))) = AMapNaviDrivingStrategySingleAvoidCost,
    AMapNaviDrivingStrategyShortDistance __attribute__ ((deprecated("use AMapNaviDrivingStrategySinglePrioritiseDistance instead"))) = AMapNaviDrivingStrategySinglePrioritiseDistance,
    AMapNaviDrivingStrategyNoExpressways __attribute__ ((deprecated("use AMapNaviDrivingStrategySingleAvoidExpressway instead"))) = AMapNaviDrivingStrategySingleAvoidExpressway,
    AMapNaviDrivingStrategyFastestTime __attribute__ ((deprecated("use AMapNaviDrivingStrategySingleAvoidCongestion instead"))) = AMapNaviDrivingStrategySingleAvoidCongestion,
    AMapNaviDrivingStrategyDefaultAndFastest __attribute__ ((deprecated("use AMapNaviDrivingStrategyMultipleAvoidCongestion instead"))) = AMapNaviDrivingStrategyMultipleAvoidCongestion,
    AMapNaviDrivingStrategyDefaultAndShort __attribute__ ((deprecated("use AMapNaviDrivingStrategyMultipleDefault instead"))) = AMapNaviDrivingStrategyMultipleDefault,
    AMapNaviDrivingStrategyAvoidCongestion __attribute__ ((deprecated("use AMapNaviDrivingStrategySingleAvoidCostAndCongestion instead"))) = AMapNaviDrivingStrategySingleAvoidCostAndCongestion,
    AMapNaviDrivingStrategyDefaultAndFastestAndShort __attribute__ ((deprecated("use AMapNaviDrivingStrategyMultipleAvoidCongestion instead"))) = AMapNaviDrivingStrategyMultipleAvoidCongestion,
};

/// 路径计算状态
typedef NS_ENUM(NSInteger, AMapNaviCalcRouteState)
{
    AMapNaviCalcRouteStateEnvFailed = 0,            //!< 0 Push执行环境不具备
    AMapNaviCalcRouteStateSucceed = 1,              //!< 1 路径计算成功/Push数据操作执行成功
    AMapNaviCalcRouteStateNetworkError = 2,         //!< 2 网络超时或网络失败
    AMapNaviCalcRouteStateParamInvalid = AMapNaviCalcRouteStateNetworkError,//!< 2 Push数据包含无效参数、不合理参数
    AMapNaviCalcRouteStateStartPointError = 3,      //!< 3 起点错误
    AMapNaviCalcRouteStateProtocolError,            //!< 4 协议解析错误
    AMapNaviCalcRouteStateCallCenterError,          //!< 5 呼叫中心错误
    AMapNaviCalcRouteStateEndPointError,            //!< 6 终点错误
    AMapNaviCalcRouteStateEncodeFalse,              //!< 7 服务端编码错误
    AMapNaviCalcRouteStateLackPreview,              //!< 8 数据缺乏预览数据
    AMapNaviCalcRouteStateDataBufError,             //!< 9 数据格式错误
    AMapNaviCalcRouteStateStartRouteError,          //!< 10 起点没有找到道路
    AMapNaviCalcRouteStateEndRouteError,            //!< 11 没有找到通向终点的道路
    AMapNaviCalcRouteStatePassRouteError,           //!< 12 没有找到通向途经点的道路
    AMapNaviCalcRouteStateRouteFail,                //!< 13 算路失败（未知错误）
    AMapNaviCalcRouteStateForbid = 100,             //!< 100 Push数据操作执行时机不当，拒绝执行
    
};

/// 导航段转向图标类型
typedef NS_ENUM(NSInteger, AMapNaviIconType)
{
    AMapNaviIconTypeNone = 0,                       //!< 0 无定义
    AMapNaviIconTypeDefault,                        //!< 1 车图标
    AMapNaviIconTypeLeft,                           //!< 2 左转图标
    AMapNaviIconTypeRight,                          //!< 3 右转图标
    AMapNaviIconTypeLeftFront,                      //!< 4 左前方图标
    AMapNaviIconTypeRightFront,                     //!< 5 右前方图标
    AMapNaviIconTypeLeftBack,                       //!< 6 左后方图标
    AMapNaviIconTypeRightBack,                      //!< 7 右后方图标
    AMapNaviIconTypeLeftAndAround,                  //!< 8 左转掉头图标
    AMapNaviIconTypeStraight,                       //!< 9 直行图标
    AMapNaviIconTypeArrivedWayPoint,                //!< 10 到达途经点图标
    AMapNaviIconTypeEnterRoundabout,                //!< 11 进入环岛图标
    AMapNaviIconTypeOutRoundabout,                  //!< 12 驶出环岛图标
    AMapNaviIconTypeArrivedServiceArea,             //!< 13 到达服务区图标
    AMapNaviIconTypeArrivedTollGate,                //!< 14 到达收费站图标
    AMapNaviIconTypeArrivedDestination,             //!< 15 到达目的地图标
    AMapNaviIconTypeArrivedTunnel,                  //!< 16 进入隧道图标
    AMapNaviIconTypeCrosswalk,                      //!< 17 通过人行横道图标
    AMapNaviIconTypeFlyover,                        //!< 18 通过过街天桥图标
    AMapNaviIconTypeUnderpass,                      //!< 19 通过地下通道图标
};

/// 导航播报类型
typedef NS_ENUM(NSInteger, AMapNaviSoundType)
{
    AMapNaviSoundTypeNaviInfo = 1,                  //!< 1 导航播报
    AMapNaviSoundTypeFrontTraffic = 2,              //!< 2 前方路况
    AMapNaviSoundTypeSurroundingTraffic = 4,        //!< 4 周边路况
    AMapNaviSoundTypePassedReminder = 8,            //!< 8 通过提示
};

/// 非导航状态电子眼播报类型
typedef NS_ENUM(NSInteger,AMapNaviDetectedMode)
{
    AMapNaviDetectedModeNone = 0,                   //!< 0 关闭所有
    AMapNaviDetectedModeCamera,                     //!< 1 仅电子眼
    AMapNaviDetectedModeSpecialRoad,                //!< 2 仅特殊道路设施
    AMapNaviDetectedModeCameraAndSpecialRoad,       //!< 3 电子眼和特殊道路设施
};

/// AMapNaviLink的道路类型
typedef NS_ENUM(NSInteger, AMapNaviRoadClass)
{
    AMapNaviRoadClassHighWay = 0,                   //!< 0 高速公路
    AMapNaviRoadClassNationalRoad,                  //!< 1 国道
    AMapNaviRoadClassProvincialRoad,                //!< 2 省道
    AMapNaviRoadClassCountyRoad,                    //!< 3 县道
    AMapNaviRoadClassVillageRoad,                   //!< 4 乡公路
    AMapNaviRoadClassCountyInternalRoad,            //!< 5 县乡村内部道路
    AMapNaviRoadClassMainStreet,                    //!< 6 主要大街、城市快速道
    AMapNaviRoadClassMainRoad,                      //!< 7 主要道路
    AMapNaviRoadClassMinorRoad,                     //!< 8 次要道路
    AMapNaviRoadClassNormalRoad,                    //!< 9 普通道路
    AMapNaviRoadClassNotNaviRoad,                   //!< 10 非导航道路
};

/// AMapNaviLink的主辅路信息
typedef NS_ENUM(NSInteger, AMapNaviFormWay)
{
    AMapNaviFormWayMainRoad = 1,                    //!< 1 主路
    AMapNaviFormWayInternalRoad,                    //!< 2 路口内部道路
    AMapNaviFormWayJCT,                             //!< 3 JCT道路
    AMapNaviFormWayRoundabout,                      //!< 4 环岛
    AMapNaviFormWayRestArea,                        //!< 5 服务区
    AMapNaviFormWayRamp,                            //!< 6 匝道
    AMapNaviFormWaySideRoad,                        //!< 7 辅路
    AMapNaviFormWayRampAndJCT,                      //!< 8 匝道与JCT
    AMapNaviFormWayExit,                            //!< 9 出口
    AMapNaviFormWayEntrance,                        //!< 10 入口
    AMapNaviFormWayTurnRightRoadA,                  //!< 11 A类右转专用道
    AMapNaviFormWayTurnRightRoadB,                  //!< 12 B类右转专用道
    AMapNaviFormWayTurnLeftRoadA,                   //!< 13 A类左转专用道
    AMapNaviFormWayTurnLeftRoadB,                   //!< 14 B类左转专用道
    AMapNaviFormWayNormalRoad,                      //!< 15 普通道路
    AMapNaviFormWayTurnLeftAndRightRoad,            //!< 16 左右转专用道
    AMapNaviFormWayRestAreaAndJCT = 53,             //!< 53 服务区与JCT
    AMapNaviFormWayRestAreaAndRamp = 56,            //!< 56 服务区与匝道
    AMapNaviFormWayRestAreaRampJCT = 58,            //!< 58 服务区与匝道以及JCT
};

/// 电子眼类型
typedef NS_ENUM(NSInteger, AMapNaviCameraType)
{
    AMapNaviCameraTypeSpeed = 0,                    //!< 0 测速摄像
    AMapNaviCameraTypeSurveillance,                 //!< 1 监控摄像
    AMapNaviCameraTypeTrafficLight,                 //!< 2 闯红灯拍照
    AMapNaviCameraTypeBreakRule,                    //!< 3 违章拍照
    AMapNaviCameraTypeBusway,                       //!< 4 公交专用道摄像头
};

/// 播报模式
typedef NS_ENUM(NSInteger, AMapNaviBroadcastMode)
{
    AMapNaviBroadcastModeConcise = 1,               //!< 1 经典简洁播报(建议老司机使用)
    AMapNaviBroadcastModeDetailed,                  //!< 2 新手详细播报
};

/// 道路状态
typedef NS_ENUM(NSInteger, AMapNaviRouteStatus)
{
    AMapNaviRouteStatusUnknow = 0,                  //!< 0 未知状态
    AMapNaviRouteStatusSmooth,                      //!< 1 通畅
    AMapNaviRouteStatusSlow,                        //!< 2 缓行
    AMapNaviRouteStatusJam,                         //!< 3 阻塞
    AMapNaviRouteStatusSeriousJam,                  //!< 4 严重阻塞
};

#pragma mark - LaneInfo Image

/**
 *  创建车道信息图片
 *  
 *  @param laneBackInfo 车道背景信息
 *  @param laneSelectInfo 车道选择信息
 *  @return 车道信息图片
 */
FOUNDATION_EXTERN UIImage *CreateLaneInfoImageWithLaneInfo(NSString *laneBackInfo, NSString *laneSelectInfo);

/**
 *  将驾车路线规划的偏好设置转换为驾车路径规划策略
 *
 *  注意：当prioritiseHighway为YES时，将忽略avoidHighway和avoidCost的设置
 *
 *  @param multipleRoute 是否多路径规划
 *  @param avoidCongestion 是否躲避拥堵
 *  @param avoidHighway 是否不走高速
 *  @param avoidCost 是否避免收费
 *  @param prioritiseHighway 是否高速优先
 *  @return AMapNaviDrivingStrategy路径规划策略
 */
FOUNDATION_EXTERN AMapNaviDrivingStrategy ConvertDrivingPreferenceToDrivingStrategy(BOOL multipleRoute,
                                                                                    BOOL avoidCongestion,
                                                                                    BOOL avoidHighway,
                                                                                    BOOL avoidCost,
                                                                                    BOOL prioritiseHighway);

#pragma mark - AMapNaviPoint

@interface AMapNaviPoint : NSObject<NSCopying,NSCoding>

/**
 *  纬度
 */
@property (nonatomic, assign) CGFloat latitude;

/**
 *  经度
 */
@property (nonatomic, assign) CGFloat longitude;

/**
 *  AMapNaviPoint类对象的初始化函数
 *  @param lat 纬度
 *  @param lon 经度
 *  @return AMapNaviPoint类对象id
 */
+ (AMapNaviPoint *)locationWithLatitude:(CGFloat)lat longitude:(CGFloat)lon;

@end

#pragma mark - AMapNaviPointBounds

@interface AMapNaviPointBounds : NSObject<NSCopying,NSCoding>

/**
 *  东北角坐标
 */
@property (nonatomic, strong) AMapNaviPoint *northEast;

/**
 *  西南角坐标
 */
@property (nonatomic, strong) AMapNaviPoint *southWest;

/**
 *  AMapNaviPointBounds类对象的初始化函数
 *  @param northEast 东北角经纬度
 *  @param southWest 西南角经纬度
 *  @return AMapNaviPointBounds类对象id
 */
+ (AMapNaviPointBounds *)pointBoundsWithNorthEast:(AMapNaviPoint *)northEast southWest:(AMapNaviPoint *)southWest;

@end

#pragma mark - AMapNaviGuide

/// 导航段信息类
@interface AMapNaviGuide : NSObject<NSCopying,NSCoding>

/**
 *  导航段名称
 */
@property (nonatomic, strong) NSString *name;

/**
 *  导航段长度
 */
@property (nonatomic, assign) NSInteger length;

/**
 *  导航段时间
 */
@property (nonatomic, assign) NSInteger time;

/**
 *  导航段转向类型
 */
@property (nonatomic, assign) AMapNaviIconType iconType;

/**
 *  导航段路口点的坐标
 */
@property (nonatomic, strong) AMapNaviPoint *coordinate;

@end

#pragma mark - AMapNaviTrafficStatus

/// 前方交通路况信息类
@interface AMapNaviTrafficStatus : NSObject

/**
 *  道路状态
 */
@property (nonatomic, assign) AMapNaviRouteStatus status;

/**
 *  该交通状态的路段长度
 */
@property (nonatomic, assign) NSInteger length;

@end

#pragma mark - AMapNaviCameraInfo

/// 电子眼信息类
@interface AMapNaviCameraInfo : NSObject<NSCopying>

/**
 *  电子眼类型
 */
@property (nonatomic, assign) AMapNaviCameraType cameraType;

/**
 *  电子眼限速，若无限速信息则为0
 */
@property (nonatomic, assign) NSInteger cameraSpeed;

/**
 *  电子眼经纬度
 */
@property (nonatomic, strong) AMapNaviPoint *coordinate;

@end

#pragma mark - AMapNaviCruiseInfo

/// 巡航模式信息类
@interface AMapNaviCruiseInfo : NSObject

/**
 *  连续启用时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger cruisingDriveTime;
/**
 *  连续行驶距离(单位:米)
 */
@property (nonatomic, assign) NSInteger cruisingDriveDistance;

@end

#pragma mark - AMapNaviTrafficFacilityInfo

/**
 * 获取道路设施类型
 * 0：未知道路设施
 * 4：测速摄像头、测速雷达
 * 5：违章摄像头
 * 12：铁路道口
 * 13：注意落石（左侧）
 * 14：事故易发地段
 * 15：易滑
 * 16：村庄
 * 18：前方学校
 * 19：有人看管的铁路道口
 * 20：无人看管的铁路道口
 * 21：两侧变窄
 * 22：向左急弯路
 * 23：向右急弯路
 * 24：反向弯路
 * 25：连续弯路
 * 26：左侧合流标识牌
 * 27：右侧合流标识牌
 * 28：监控摄像头
 * 29：专用道摄像头
 * 31：禁止超车
 * 36：右侧变窄
 * 37：左侧变窄
 * 38：窄桥
 * 39：左右绕行
 * 40：左侧绕行
 * 41：右侧绕行
 * 42：注意落石（右侧）
 * 43：傍山险路（左侧）
 * 44：傍山险路（右侧）
 * 47：上陡坡
 * 48：下陡坡
 * 49：过水路面
 * 50：路面不平
 * 52：慢行
 * 53：注意危险
 * 58：隧道
 * 59：渡口
 * 92:闯红灯
 * 93:应急车道
 * 94:非机动车道
 * 100：不绑定电子眼高发地
 * 101:车道违章
 * 102:超速违章
 */

///  道路交通设施类
@interface AMapNaviTrafficFacilityInfo : NSObject

/**
 *  经纬度
 */
@property (nonatomic, strong) AMapNaviPoint *coordinate;

/**
 *  类型
 */
@property (nonatomic, assign) NSInteger boardcastType;

/**
 *  距离设施的剩余距离(单位:米)
 */
@property (nonatomic, assign) NSInteger distance;

/**
 *  限速值(单位:公里/小时)
 */
@property (nonatomic, assign) NSInteger limitSpeed;

@end
