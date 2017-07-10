//
//  AMapLocationCommonObj.h
//  AMapLocationKit
//
//  Created by AutoNavi on 15/10/22.
//  Copyright © 2015年 Amap. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>


///AMapLocation errorDomain
extern NSString * const AMapLocationErrorDomain;

///AMapLocation errorCode
typedef NS_ENUM(NSInteger, AMapLocationErrorCode)
{
    AMapLocationErrorUnknown = 1,               ///<未知错误
    AMapLocationErrorLocateFailed = 2,          ///<定位错误
    AMapLocationErrorReGeocodeFailed  = 3,      ///<逆地理错误
    AMapLocationErrorTimeOut = 4,               ///<超时
    AMapLocationErrorCanceled = 5,              ///<取消
    AMapLocationErrorCannotFindHost = 6,        ///<找不到主机
    AMapLocationErrorBadURL = 7,                ///<URL异常
    AMapLocationErrorNotConnectedToInternet = 8,///<连接异常
    AMapLocationErrorCannotConnectToHost = 9,   ///<服务器连接失败
    AMapLocationErrorRegionMonitoringFailure=10,///<地理围栏错误
    AMapLocationErrorRiskOfFakeLocation = 11,   ///<存在虚拟定位风险
};

///AMapLocation Region State
typedef NS_ENUM(NSInteger, AMapLocationRegionState)
{
    AMapLocationRegionStateUnknow = 0,          ///<未知
    AMapLocationRegionStateInside = 1,          ///<在范围内
    AMapLocationRegionStateOutside = 2,         ///<在范围外
};

///逆地理信息
@interface AMapLocationReGeocode : NSObject<NSCopying,NSCoding>

///格式化地址
@property (nonatomic, copy) NSString *formattedAddress;

///国家
@property (nonatomic, copy) NSString *country;

///省/直辖市
@property (nonatomic, copy) NSString *province;

///市
@property (nonatomic, copy) NSString *city;

///区
@property (nonatomic, copy) NSString *district;

///乡镇
@property (nonatomic, copy) NSString *township __attribute__((deprecated("该字段从v2.2.0版本起不再返回数据,建议您使用AMapSearchKit的逆地理功能获取.")));

///社区
@property (nonatomic, copy) NSString *neighborhood __attribute__((deprecated("该字段从v2.2.0版本起不再返回数据,建议您使用AMapSearchKit的逆地理功能获取.")));

///建筑
@property (nonatomic, copy) NSString *building __attribute__((deprecated("该字段从v2.2.0版本起不再返回数据,建议您使用AMapSearchKit的逆地理功能获取.")));

///城市编码
@property (nonatomic, copy) NSString *citycode;

///区域编码
@property (nonatomic, copy) NSString *adcode;

///街道名称
@property (nonatomic, copy) NSString *street;

///门牌号
@property (nonatomic, copy) NSString *number;

///兴趣点名称
@property (nonatomic, copy) NSString *POIName;

///所属兴趣点名称
@property (nonatomic, copy) NSString *AOIName;

@end

#pragma mark - AMapLocationPoint

///经纬度坐标点对象
@interface AMapLocationPoint : NSObject<NSCopying,NSCoding>

///纬度
@property (nonatomic, assign) CGFloat latitude;

///经度
@property (nonatomic, assign) CGFloat longitude;

/**
 *  @brief AMapNaviPoint类对象的初始化函数
 *  @param lat 纬度
 *  @param lon 经度
 *  @return AMapNaviPoint类对象id
 */
+ (AMapLocationPoint *)locationWithLatitude:(CGFloat)lat longitude:(CGFloat)lon;

@end

///POI信息
@interface AMapLocationPOIItem : NSObject <NSCopying, NSCoding>

///id
@property (nonatomic, copy) NSString *pId;

///名称
@property (nonatomic, copy) NSString *name;

///类型
@property (nonatomic, copy) NSString *type;

///类型编码
@property (nonatomic, copy) NSString *typeCode;

///地址信息
@property (nonatomic, copy) NSString *address;

///经纬度
@property (nonatomic, strong) AMapLocationPoint *location;

///电话号码
@property (nonatomic, copy) NSString *tel;

///省份
@property (nonatomic, copy) NSString *province;

///城市
@property (nonatomic, copy) NSString *city;

///区
@property (nonatomic, copy) NSString *district;

@end

///行政区域信息
@interface AMapLocationDistrictItem : NSObject <NSCopying, NSCoding>

///城市编码
@property (nonatomic, copy) NSString *cityCode;

///区域编码
@property (nonatomic, copy) NSString *districtCode;

///区名
@property (nonatomic, copy) NSString *district;

///行政区域轮廓坐标点，每个行政区可能有多个模块,每个模块的坐标点数组由AMapLocationPoint构成
@property (nonatomic, copy) NSArray <NSArray<AMapLocationPoint *> *> *polylinePoints;

@end

///AMapLocation CoordinateType
typedef NS_ENUM(NSUInteger, AMapLocationCoordinateType)
{
    AMapLocationCoordinateTypeBaidu = 0,        ///<Baidu
    AMapLocationCoordinateTypeMapBar,           ///<MapBar
    AMapLocationCoordinateTypeMapABC,           ///<MapABC
    AMapLocationCoordinateTypeSoSoMap,          ///<SoSoMap
    AMapLocationCoordinateTypeAliYun,           ///<AliYun
    AMapLocationCoordinateTypeGoogle,           ///<Google
    AMapLocationCoordinateTypeGPS,              ///<GPS
};

/**
 *  @brief 转换目标经纬度为高德坐标系
 *  @param coordinate 待转换的经纬度
 *  @param type       坐标系类型
 *  @return 高德坐标系经纬度
 */
FOUNDATION_EXTERN CLLocationCoordinate2D AMapLocationCoordinateConvert(CLLocationCoordinate2D coordinate, AMapLocationCoordinateType type);

/**
 *  @brief 判断目标经纬度是否在大陆以及港、澳地区。输入参数为高德坐标系。
 *  @param coordinate 待判断的目标经纬度
 *  @return 是否在大陆以及港、澳地区
 */
FOUNDATION_EXTERN BOOL AMapLocationDataAvailableForCoordinate(CLLocationCoordinate2D coordinate);
