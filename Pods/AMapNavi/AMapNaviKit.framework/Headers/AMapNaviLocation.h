//
//  AMapNaviLocation.h
//  AMapNaviKit
//
//  Created by AutoNavi on 14-7-7.
//  Copyright (c) 2014年 AutoNavi. All rights reserved.
//

#import "AMapNaviCommonObj.h"

/**
 *  当前的自车位置
 */
@interface AMapNaviLocation : NSObject<NSCopying>

/**
 *  经纬度
 */
@property (nonatomic, strong) AMapNaviPoint *coordinate;

/**
 *  精确度
 */
@property (nonatomic, assign) double accuracy;

/**
 *  高度
 */
@property (nonatomic, assign) double altitude;

/**
 *  方向
 */
@property (nonatomic, assign) NSInteger heading;

/**
 *  速度(km/h)
 */
@property (nonatomic, assign) NSInteger speed;

/**
 *  时间戳
 */
@property (nonatomic, strong) NSDate *timestamp;

/**
 *  是否匹配在道路上
 */
@property (nonatomic, assign) BOOL isMatchNaviPath;

@end
