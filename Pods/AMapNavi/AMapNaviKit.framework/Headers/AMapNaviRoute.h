//
//  AMapNaviRoute.h
//  AMapNaviKit
//
//  Created by AutoNavi on 14-7-11.
//  Copyright (c) 2014年 AutoNavi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMapNaviCommonObj.h"

/// AMapNaviLink --组成--> AMapNaviSegment --组成--> AMapNaviRoute

#pragma mark - AMapNaviLink

/**
 *  分段的Link信息
 */
@interface AMapNaviLink : NSObject<NSCopying>

/**
 *  Link的所有坐标
 */
@property (nonatomic, strong) NSArray<AMapNaviPoint *> *coordinates;

/**
 *  Link的长度(单位:米)
 */
@property (nonatomic, assign) NSInteger length;

/**
 *  Link的预估时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger time;

/**
 *  Link的道路名称
 */
@property (nonatomic, strong) NSString *roadName;

/**
 *  Link的道路类型
 */
@property (nonatomic, assign) AMapNaviRoadClass roadClass;

/**
 *  Link的FormWay信息
 */
@property (nonatomic, assign) AMapNaviFormWay formWay;

/**
 *  Link是否有红绿灯
 */
@property (nonatomic, assign) BOOL isHadTrafficLights;

@end

#pragma mark - AMapNaviSegment

/**
 *  路径的分段信息
 */
@interface AMapNaviSegment : NSObject<NSCopying>

/**
 *  分段的所有坐标
 */
@property (nonatomic, strong) NSArray<AMapNaviPoint *> *coordinates;

/**
 *  分段的所有Link
 */
@property (nonatomic, strong) NSArray<AMapNaviLink *> *links;

/**
 *  分段的长度(单位:米)
 */
@property (nonatomic, assign) NSInteger length;

/**
 *  分段的预估时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger time;

/**
 *  分段的转向类型
 */
@property (nonatomic, assign) AMapNaviIconType iconType;

/**
 *  分段的收费路长度(单位:米)
 */
@property (nonatomic, assign) NSInteger chargeLength;

/**
 *  分段的收费金额
 */
@property (nonatomic, assign) NSInteger tollCost;

@end

#pragma mark - AMapNaviRoute

/**
 *  导航路径信息
 */
@interface AMapNaviRoute : NSObject<NSCopying>

/**
 *  导航路径总长度(单位:米)
 */
@property (nonatomic, assign) NSInteger routeLength;

/**
 *  导航路径所需的时间(单位:秒)
 */
@property (nonatomic, assign) NSInteger routeTime;

/**
 *  导航路线最小坐标点和最大坐标点围成的矩形区域
 */
@property (nonatomic, strong) AMapNaviPointBounds *routeBounds;

/**
 *  导航路线的中心点，即导航路径的最小外接矩形对角线的交点
 */
@property (nonatomic, strong) AMapNaviPoint *routeCenterPoint;

/**
 *  导航路线的所有形状点
 */
@property (nonatomic, strong) NSArray<AMapNaviPoint *> *routeCoordinates;

/**
 *  路线方案的起点坐标
 */
@property (nonatomic, strong) AMapNaviPoint *routeStartPoint;

/**
 *  路线方案的终点坐标
 */
@property (nonatomic, strong) AMapNaviPoint *routeEndPoint;

/**
 *  导航路线的所有分段
 */
@property (nonatomic, strong) NSArray<AMapNaviSegment *> *routeSegments;

/**
 *  导航路线上分段的总数
 */
@property (nonatomic, assign) NSInteger routeSegmentCount;

/**
 *  导航路线上的所有电子眼
 */
@property (nonatomic, strong) NSArray<AMapNaviCameraInfo *> *routeCameras;

/**
 *  导航路线上红绿灯的总数
 */
@property (nonatomic, assign) NSInteger routeTrafficLightCount;

/**
 *  导航路线的路径计算策略(只适用于驾车路径规划)
 */
@property (nonatomic, assign) AMapNaviDrivingStrategy routeStrategy;

/**
 *  导航路线的花费金额(单位:元)
 */
@property (nonatomic, assign) NSInteger routeTollCost;

/**
 *  路径的途经点坐标
 */
@property (nonatomic, strong) NSArray<AMapNaviPoint *> *wayPoints;

/**
 *  路径的途经点所在segment段的index
 */
@property (nonatomic, strong) NSIndexPath *wayPointsIndexes;

/**
 *  路径的途经点在routeCoordinates上对应的index
 */
@property (nonatomic, strong) NSArray<NSNumber *> *wayPointCoordIndexes;

@end
