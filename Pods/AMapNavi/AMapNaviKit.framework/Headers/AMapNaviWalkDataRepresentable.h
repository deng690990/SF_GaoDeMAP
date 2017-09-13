//
//  AMapNaviWalkDataRepresentable.h
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
@class AMapNaviWalkManager;

/**
 *  AMapNaviWalkDataRepresentable协议
 *
 *  实例对象可以通过实现该协议,并将其通过 AMapNaviWalkManager 的addDataRepresentative:方法进行注册,便可获取导航过程中的导航数据更新.
 *
 *  可以根据不同需求,选取使用特定的数据进行导航界面自定义. AMapNaviWalkView 即通过该协议实现导航过程展示.
 *
 *  也可以依据导航数据的更新进行其他的逻辑处理.
 */
@protocol AMapNaviWalkDataRepresentable <NSObject>

@optional

/**
 *  导航模式更新回调
 *
 *  @param naviMode 导航模式,参考AMapNaviMode
 */
- (void)walkManager:(AMapNaviWalkManager *)walkManager updateNaviMode:(AMapNaviMode)naviMode;

/**
 *  路径ID更新回调
 *
 *  @param naviRouteID 导航路径ID
 */
- (void)walkManager:(AMapNaviWalkManager *)walkManager updateNaviRouteID:(NSInteger)naviRouteID;

/**
 *  路径信息更新回调
 *
 *  @param naviRoute 路径信息,参考 AMapNaviRoute 类
 */
- (void)walkManager:(AMapNaviWalkManager *)walkManager updateNaviRoute:(nullable AMapNaviRoute *)naviRoute;

/**
 *  导航信息更新回调
 *
 *  @param naviInfo 导航信息,参考 AMapNaviInfo 类
 */
- (void)walkManager:(AMapNaviWalkManager *)walkManager updateNaviInfo:(nullable AMapNaviInfo *)naviInfo;

/**
 *  自车位置更新回调
 *
 *  @param naviLocation 自车位置信息,参考 AMapNaviLocation 类
 */
- (void)walkManager:(AMapNaviWalkManager *)walkManager updateNaviLocation:(nullable AMapNaviLocation *)naviLocation;

@end

NS_ASSUME_NONNULL_END
