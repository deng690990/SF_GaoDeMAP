//
//  GeographyConfigModel.h
//  SF_GaoDeMAP
//
//  Created by 邓升发 on 2019/3/6.
//  Copyright © 2019年 ShouNew.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AMapLocationKit/AMapLocationKit.h>
NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, GeoType) {
    GeoType_circle = 0,//圆形
    GeoType_polygon //多边形
};
@interface GeographyConfigModel : NSObject

//围栏颜色
@property (nonatomic,strong) UIColor *geoColor;
//围栏线条宽度
@property (nonatomic,assign) CGFloat geoLineW;
//围栏类型
@property (nonatomic,assign) GeoType geoType;
//圆形围栏半径
@property (nonatomic,assign) CGFloat reduis;
//圆形围栏中心点
@property (nonatomic,assign) CLLocationCoordinate2D centerCoordinate;
//多边形的点
@property (nonatomic,assign) CLLocationCoordinate2D *coordinates;
//多边形点的数量（3个以上）
@property (nonatomic,assign) NSInteger coordinateCount;

@end

NS_ASSUME_NONNULL_END
