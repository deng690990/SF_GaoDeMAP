//
//  AMapNaviRoutePolylineOption.h
//  AMapNaviKit
//
//  Created by liubo on 7/26/16.
//  Copyright © 2016 AutoNavi. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  导航路线Polyline的显示样式
 */
@interface AMapNaviRoutePolylineOption : NSObject <NSCopying>

/**
 *  笔触宽度,默认是0
 */
@property (nonatomic, assign) NSInteger lineWidth;

/**
 *  绘制索引数组(纹理、颜色索引数组), 成员为NSNumber, 且为非负数
 */
@property (nonatomic, copy) NSArray<NSNumber *> *drawStyleIndexes;

/**
 *  分段纹理图片
 *
 *  纹理图片需满足: 长宽相等,且宽度值为2的次幂
 */
@property (nonatomic, copy) NSArray<UIImage *> *textureImages;

/**
 *  分段绘制的颜色
 *
 *  当同时设置textureImages和strokeColors时，strokeColors设置将被忽略
 */
@property (nonatomic, copy) NSArray<UIColor *> *strokeColors;

/**
 *  是否替换掉实时交通Polyline,默认NO
 */
@property (nonatomic, assign) BOOL replaceTrafficPolyline;

@end
