//
//  AMapNaviInfo.h
//  AMapNaviKit
//
//  Created by AutoNavi on 14-8-22.
//  Copyright (c) 2014年 AutoNavi. All rights reserved.
//

#import "AMapNaviCommonObj.h"

/**
 *  导航过程中的导航信息
 */
@interface AMapNaviInfo : NSObject<NSCopying,NSCoding>

/**
 *  导航信息更新类型
 */
@property (nonatomic, assign) AMapNaviMode naviMode;

/**
 *  导航段转向图标类型
 */
@property (nonatomic, assign) AMapNaviIconType iconType;

/**
 *  自车方向,单位度(正北为0,顺时针增加)
 */
@property (nonatomic, assign) NSInteger carDirection;

/**
 *  自车经纬度
 */
@property (nonatomic, strong) AMapNaviPoint *carCoordinate;

/**
 *  当前道路名称
 */
@property (nonatomic, strong) NSString *currentRoadName;

/**
 *  下条道路名称
 */
@property (nonatomic, strong) NSString *nextRoadName;

/**
 *  离终点剩余距离(单位:米)
 */
@property (nonatomic, assign) NSInteger routeRemainDistance;

/**
 *  离终点预估剩余时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger routeRemainTime;

/**
 *  当前所在的segment段的index,从0开始
 */
@property (nonatomic, assign) NSInteger currentSegmentIndex;

/**
 *  当前路段剩余距离(单位:米)
 */
@property (nonatomic, assign) NSInteger segmentRemainDistance;

/**
 *  当前路段预估剩余时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger segmentRemainTime;

/**
 *  当前所在的link段的index,从0开始
 */
@property (nonatomic, assign) NSInteger currentLinkIndex;

/// 以下导航信息仅在驾车导航时有效

/**
 *  电子眼在路径上的编号,总是指下一个将要路过的电子眼的编号,若为-1则路上没有电子眼
 */
@property (nonatomic, assign) NSInteger cameraIndex;

/**
 *  电子眼距离(单位:米; -1为没有电子眼或距离很远)
 */
@property (nonatomic, assign) NSInteger cameraDistance;

/**
 *  电子眼类型(0为测速摄像头,1为监控摄像头)
 */
@property (nonatomic, assign) NSInteger cameraType;

/**
 *  电子眼经纬度
 */
@property (nonatomic, strong) AMapNaviPoint *cameraCoordinate;

/**
 *  电子眼限速(0为无限速信息)
 */
@property (nonatomic, assign) NSInteger cameraLimitSpeed;

/**
 *  离服务站距离(单位:米; -1为没有服务站)
 */
@property (nonatomic, assign) NSInteger serviceAreaDistance;

@end
