//
//  AMapSearchObj.h
//  AMapSearchKit
//
//  Created by xiaoming han on 15/7/22.
//  Copyright (c) 2015年 Amap. All rights reserved.
//

/* 该文件定义了搜索请求和返回对象。*/

#import <Foundation/Foundation.h>
#import "AMapCommonObj.h"

///沿途搜索类型
typedef NS_ENUM(NSInteger, AMapRoutePOISearchType)
{
    AMapRoutePOISearchTypeGasStation         = 0,   ///< 加油站
    AMapRoutePOISearchTypeMaintenanceStation = 1,   ///< 维修站
    AMapRoutePOISearchTypeATM                = 2,   ///< ATM
    AMapRoutePOISearchTypeToilet             = 3,   ///< 厕所
    AMapRoutePOISearchTypeGasAirStation      = 4,   ///< 加气站
    AMapRoutePOISearchTypeParkStation        = 5,   ///< 服务区
};

///天气查询类型
typedef NS_ENUM(NSInteger, AMapWeatherType)
{
    AMapWeatherTypeLive = 1,    ///< 实时
    AMapWeatherTypeForecast     ///< 预报
};

///云图搜索结果排序
typedef NS_ENUM(NSInteger, AMapCloudSortType)
{
    AMapCloudSortTypeDESC      = 0, ///< 降序
    AMapCloudSortTypeASC       = 1  ///< 升序
};

///附近搜索距离类型
typedef NS_ENUM(NSInteger, AMapNearbySearchType)
{
    AMapNearbySearchTypeLiner   = 0, ///< 直线距离
    AMapNearbySearchTypeDriving = 1, ///< 驾车行驶距离
};

#pragma mark - AMapPOISearchBaseRequest

///POI搜索请求基类
@interface AMapPOISearchBaseRequest : AMapSearchObject
///类型，多个类型用“|”分割 可选值:文本分类、分类代码
@property (nonatomic, copy)   NSString  *types;
///排序规则, 0-距离排序；1-综合排序, 默认0
@property (nonatomic, assign) NSInteger  sortrule;
///每页记录数, 范围1-50, [default = 20]
@property (nonatomic, assign) NSInteger  offset;
///当前页数, 范围1-100, [default = 1]
@property (nonatomic, assign) NSInteger  page;
///建筑物POI编号，传入建筑物POI之后，则只在该建筑物之内进行搜索 since 4.5.0
@property (nonatomic, copy) NSString *building;
///是否返回扩展信息，默认为 NO。
@property (nonatomic, assign) BOOL requireExtension;
///是否返回子POI，默认为 NO。
@property (nonatomic, assign) BOOL requireSubPOIs;
@end

///POI ID搜索请求
@interface AMapPOIIDSearchRequest : AMapPOISearchBaseRequest
///POI全局唯一ID
@property (nonatomic, copy) NSString *uid; 
@end

///POI关键字搜索
@interface AMapPOIKeywordsSearchRequest : AMapPOISearchBaseRequest
///查询关键字，多个关键字用“|”分割
@property (nonatomic, copy)   NSString *keywords; 
///查询城市，可选值：cityname（中文或中文全拼）、citycode、adcode.(注：台湾地区一律设置为【台湾】，不具体到市。)
@property (nonatomic, copy)   NSString *city; 
///强制城市限制功能 默认NO，例如：在上海搜索天安门，如果citylimit为true，将不返回北京的天安门相关的POI
@property (nonatomic, assign) BOOL cityLimit;

@end

///POI周边搜索
@interface AMapPOIAroundSearchRequest : AMapPOISearchBaseRequest
///查询关键字，多个关键字用“|”分割
@property (nonatomic, copy)   NSString     *keywords; 
///中心点坐标
@property (nonatomic, copy)   AMapGeoPoint *location; 
///查询半径，范围：0-50000，单位：米 [default = 3000]
@property (nonatomic, assign) NSInteger     radius; 
@end

///POI多边形搜索
@interface AMapPOIPolygonSearchRequest : AMapPOISearchBaseRequest
///查询关键字，多个关键字用“|”分割
@property (nonatomic, copy) NSString       *keywords; 
///多边形
@property (nonatomic, copy) AMapGeoPolygon *polygon; 
@end

///POI搜索返回
@interface AMapPOISearchResponse : AMapSearchObject
///返回的POI数目
@property (nonatomic, assign) NSInteger       count; 
///关键字建议列表和城市建议列表
@property (nonatomic, strong) AMapSuggestion *suggestion; 
///POI结果，AMapPOI 数组
@property (nonatomic, strong) NSArray<AMapPOI *> *pois; 
@end

#pragma mark - AMapPOIRouteSearchRequest
///沿途搜索, 注意起点和终点不能相距太远(大概70公里)，否则可能搜索结果为空
@interface AMapRoutePOISearchRequest : AMapSearchObject
///中心点坐标
@property (nonatomic, copy)   AMapGeoPoint *origin; 
///目标点坐标
@property (nonatomic, copy)   AMapGeoPoint *destination; 
///搜索类型
@property (nonatomic, assign) AMapRoutePOISearchType searchType; 
///驾车导航策略，同驾车路径规划请求的策略（5 多策略除外）
@property (nonatomic, assign) NSInteger strategy;
///道路周围搜索范围,单位米,[0-500]，默认250。
@property (nonatomic, assign) NSInteger range;
///用户自己规划的路线,在origine、destination未填入时为必填.格式为:"经度,维度;经度,维度;...". 目前限制个数最多为100个点
@property (nonatomic, strong) NSString *polylineStr;
///用户自己规划的路线,在origine、destination未填入且polylineStr未填入时为必填. 目前限制个数最多为100个点
@property (nonatomic, strong) NSArray<AMapGeoPoint*> *polyline;

@end

///沿途搜索返回
@interface AMapRoutePOISearchResponse : AMapSearchObject
///返回的POI数目
@property (nonatomic, assign) NSInteger count; 
///POI结果，AMapRoutePOI 数组
@property (nonatomic, strong) NSArray<AMapRoutePOI *> *pois; 
@end

#pragma mark - AMapInputTipsSearchRequest

///搜索提示请求
@interface AMapInputTipsSearchRequest : AMapSearchObject
///查询关键字
@property (nonatomic, copy)   NSString *keywords; 
///查询城市，可选值：cityname（中文或中文全拼）、citycode、adcode.
@property (nonatomic, copy)   NSString *city; 
///类型，多个类型用“|”分割 可选值:文本分类、分类代码
@property (nonatomic, copy)   NSString *types; 
///强制城市限制功能，例如：在上海搜索天安门，如果citylimit为true，将不返回北京的天安门相关的POI
@property (nonatomic, assign) BOOL cityLimit;
///格式形如：@"116.481488,39.990464",(经度,纬度)，不可以包含空格。如果设置，在此location附近优先返回搜索关键词信息, since 5.0.0
@property (nonatomic, copy) NSString *location;
@end

///搜索提示返回
@interface AMapInputTipsSearchResponse : AMapSearchObject
///返回数目
@property (nonatomic, assign) NSInteger  count; 
///提示列表 AMapTip 数组， AMapTip 有多种属性，可根据该对象的返回信息，配合其他搜索服务使用，完善您应用的功能。如：\n 1）uid为空，location为空，该提示语为品牌词，可根据该品牌词进行POI关键词搜索。\n 2）uid不为空，location为空，为公交线路，根据uid进行公交线路查询。\n 3）uid不为空，location也不为空，是一个真实存在的POI，可直接显示在地图上。
@property (nonatomic, strong) NSArray<AMapTip *> *tips; 
@end

#pragma mark - AMapGeocodeSearchRequest

///地理编码请求
@interface AMapGeocodeSearchRequest : AMapSearchObject
///地址
@property (nonatomic, copy) NSString *address;
///查询城市，可选值：cityname（中文或中文全拼）、citycode、adcode.
@property (nonatomic, copy) NSString *city; 
@end

///地理编码请求
@interface AMapGeocodeSearchResponse : AMapSearchObject
///返回数目
@property (nonatomic, assign) NSInteger  count; 
///地理编码结果 AMapGeocode 数组
@property (nonatomic, strong) NSArray<AMapGeocode *> *geocodes; 
@end


#pragma mark - AMapReGeocodeSearchRequest

///逆地理编码请求
@interface AMapReGeocodeSearchRequest : AMapSearchObject
///是否返回扩展信息，默认NO。
@property (nonatomic, assign) BOOL          requireExtension; 
///中心点坐标。
@property (nonatomic, copy)   AMapGeoPoint *location; 
///查询半径，单位米，范围0~3000，默认1000。
@property (nonatomic, assign) NSInteger     radius;
///指定返回结果poi数组中的POI类型，在requireExtension=YES时生效。输入为typecode, 支持传入多个typecode, 多值时用“|”分割
@property (nonatomic, copy) NSString *poitype;
@end

///逆地理编码返回
@interface AMapReGeocodeSearchResponse : AMapSearchObject
///逆地理编码结果
@property (nonatomic, strong) AMapReGeocode *regeocode; 
@end

#pragma mark - AMapBusStopSearchRequest

///公交站点请求
@interface AMapBusStopSearchRequest : AMapSearchObject
///查询关键字
@property (nonatomic, copy)   NSString  *keywords; 
///城市 可选值：cityname（中文或中文全拼）、citycode、adcode
@property (nonatomic, copy)   NSString  *city; 
///每页记录数，默认为20，取值为：1-50
@property (nonatomic, assign) NSInteger  offset; 
///当前页数，默认值为1，取值为：1-100
@property (nonatomic, assign) NSInteger  page; 
@end

///公交站点返回
@interface AMapBusStopSearchResponse : AMapSearchObject
///公交站数目
@property (nonatomic, assign) NSInteger       count; 
///关键字建议列表和城市建议列表
@property (nonatomic, strong) AMapSuggestion *suggestion; 
///公交站点数组，数组中存放AMapBusStop对象
@property (nonatomic, strong) NSArray<AMapBusStop *> *busstops; 
@end

#pragma mark - AMapBusLineSearchRequest

///公交线路查询请求基类，不可直接调用
@interface AMapBusLineBaseSearchRequest : AMapSearchObject
///城市 可选值：cityname（中文或中文全拼）、citycode、adcode
@property (nonatomic, copy)   NSString  *city; 
///是否返回扩展信息，默认为NO
@property (nonatomic, assign) BOOL       requireExtension; 
///每页记录数，默认为20，取值为1－50
@property (nonatomic, assign) NSInteger  offset; 
///当前页数，默认为1，取值为1-100
@property (nonatomic, assign) NSInteger  page; 
@end

///公交站线路根据名字请求
@interface AMapBusLineNameSearchRequest : AMapBusLineBaseSearchRequest
///查询关键字
@property (nonatomic, copy) NSString *keywords; 
@end

///公交站线路根据ID请求
@interface AMapBusLineIDSearchRequest : AMapBusLineBaseSearchRequest
///唯一标识
@property (nonatomic, copy) NSString *uid;
@end

///公交站线路返回
@interface AMapBusLineSearchResponse : AMapSearchObject
///返回公交站数目
@property (nonatomic, assign) NSInteger       count; 
///关键字建议列表和城市建议列表
@property (nonatomic, strong) AMapSuggestion *suggestion; 
///公交线路数组，数组中存放 AMapBusLine 对象
@property (nonatomic, strong) NSArray<AMapBusLine *> *buslines; 
@end

#pragma mark - AMapDistrictSearchRequest
///行政区划查询请求
@interface AMapDistrictSearchRequest : AMapSearchObject
///查询关键字，只支持单关键字搜索，全国范围
@property (nonatomic, copy)   NSString *keywords;
///是否返回边界坐标，默认NO
@property (nonatomic, assign) BOOL      requireExtension; 
///是否显示商圈信息，默认NO。
@property (nonatomic, assign) BOOL      showBusinessArea; 
@end

///行政区划响应
@interface AMapDistrictSearchResponse : AMapSearchObject
///返回数目
@property (nonatomic, assign) NSInteger  count; 
///行政区域 AMapDistrict 数组
@property (nonatomic, strong) NSArray<AMapDistrict *> *districts; 
@end

#pragma mark - AMapRouteSearchBaseRequest

///路径规划基础类，不可直接调用
@interface AMapRouteSearchBaseRequest : AMapSearchObject
///出发点
@property (nonatomic, copy) AMapGeoPoint *origin; 
///目的地
@property (nonatomic, copy) AMapGeoPoint *destination; 
@end

#pragma mark - AMapDrivingRouteSearchRequest

///驾车路径规划
@interface AMapDrivingRouteSearchRequest : AMapRouteSearchBaseRequest
///驾车导航策略([default = 0])\n 0速度优先（时间)\n 1费用优先（不走收费路段的最快道路）\n 2距离优先\n 3不走快速路\n 4躲避拥堵\n 5多策略（同时使用速度优先、费用优先、距离优先三个策略计算路径）。其中必须说明，就算使用三个策略算路，会根据路况不固定的返回一~三条路径规划信息\n 6不走高速\n 7不走高速且避免收费\n 8躲避收费和拥堵\n 9不走高速且躲避收费和拥堵\n 10多备选，时间最短，距离最短，躲避拥堵（考虑路况）\n 11多备选，时间最短，距离最短\n 12多备选，躲避拥堵（考虑路况）\n 13多备选，不走高速\n 14多备选，费用优先\n 15多备选，躲避拥堵，不走高速（考虑路况）\n 16多备选，费用有限，不走高速\n 17多备选，躲避拥堵，费用优先（考虑路况）\n 18多备选，躲避拥堵，不走高速，费用优先（考虑路况）\n 19多备选，高速优先\n 20多备选，高速优先，躲避拥堵（考虑路况）
@property (nonatomic, assign) NSInteger strategy;
///途经点 AMapGeoPoint 数组，最多支持16个途经点
@property (nonatomic, copy) NSArray<AMapGeoPoint *> *waypoints;
///避让区域 AMapGeoPolygon 数组，最多支持100个避让区域，每个区域16个点
@property (nonatomic, copy) NSArray<AMapGeoPolygon *> *avoidpolygons;
///避让道路名
@property (nonatomic, copy) NSString *avoidroad;
///出发点 POI ID
@property (nonatomic, copy) NSString *originId;
///目的地 POI ID
@property (nonatomic, copy) NSString *destinationId;
///出发点POI类型编码
@property (nonatomic, copy) NSString *origintype;
///目的地POI类型编码
@property (nonatomic, copy) NSString *destinationtype;
///是否返回扩展信息，默认为 NO
@property (nonatomic, assign) BOOL requireExtension;
///车牌省份，用汉字填入车牌省份缩写。用于判断是否限行
@property (nonatomic, copy) NSString *plateProvince;
///车牌详情,填入除省份及标点之外的字母和数字（需大写）。用于判断是否限行。
@property (nonatomic, copy) NSString *plateNumber;

@end

#pragma mark - AMapWalkingRouteSearchRequest

///步行路径规划
@interface AMapWalkingRouteSearchRequest : AMapRouteSearchBaseRequest
///是否提供备选步行方案([default = 0])0-只提供一条步行方案; 1-提供备选步行方案(有可能无备选方案)
@property (nonatomic, assign) NSInteger multipath __attribute__((deprecated("已废弃, from 5.0.0")));
@end

#pragma mark - AMapTransitRouteSearchRequest

///公交路径规划
@interface AMapTransitRouteSearchRequest : AMapRouteSearchBaseRequest
///公交换乘策略([default = 0])\n 0-最快捷模式；\n 1-最经济模式；\n 2-最少换乘模式；\n 3-最少步行模式；\n 4-最舒适模式；\n 5-不乘地铁模式
@property (nonatomic, assign) NSInteger strategy; 
///城市, 必填
@property (nonatomic, copy)   NSString *city; 
///目的城市, 跨城时需要填写，否则会出错
@property (nonatomic, copy)   NSString *destinationCity; 
///是否包含夜班车，默认为 NO
@property (nonatomic, assign) BOOL nightflag; 
///是否返回扩展信息，默认为 NO
@property (nonatomic, assign) BOOL requireExtension;
@end

#pragma mark - AMapRidingRouteSearchRequest

///骑行路径规划
@interface AMapRidingRouteSearchRequest : AMapRouteSearchBaseRequest
///路径方案类型([default = 0])\n 0-推荐路线及最快路线综合\n 1-推荐路线\n 2-最快路线
@property (nonatomic, assign) NSInteger type __attribute__((deprecated("已废弃, from 5.0.0")));
@end

///路径规划返回
@interface AMapRouteSearchResponse : AMapSearchObject
///路径规划信息数目
@property (nonatomic, assign) NSInteger count; 
///路径规划信息
@property (nonatomic, strong) AMapRoute *route; 
@end

///骑行路径规划返回
@interface AMapRidingRouteSearchResponse : AMapRouteSearchResponse
@end

#pragma mark - AMapWeatherSearchRequest

///天气查询请求
@interface AMapWeatherSearchRequest : AMapSearchObject
///城市名称，支持cityname及adcode
@property (nonatomic, copy)   NSString        *city; 
///气象类型，Live为实时天气，Forecast为后三天预报天气，默认为Live
@property (nonatomic, assign) AMapWeatherType  type; 
@end

///天气查询返回
@interface AMapWeatherSearchResponse : AMapSearchObject
///实时天气数据信息 AMapLocalWeatherLive 数组，仅在请求实时天气时有返回。
@property (nonatomic, strong) NSArray<AMapLocalWeatherLive *> *lives; 
///预报天气数据信息 AMapLocalWeatherForecast 数组，仅在请求预报天气时有返回
@property (nonatomic, strong) NSArray<AMapLocalWeatherForecast *> *forecasts; 

@end

#pragma mark - AMapRoadTrafficSearchRequest
///道路实时路况查询请求 since 5.1.0
@interface AMapRoadTrafficSearchRequest : AMapSearchObject
///道路名称，可通过逆地理编码查询获取
@property (nonatomic, copy)   NSString *roadName;
///adcode，可通过逆地理编码查询获取
@property (nonatomic, copy)   NSString *adcode;
///是否返回扩展信息，默认为 NO
@property (nonatomic, assign) BOOL requireExtension;
@end

///道路实时路况查询返回 since 5.1.0
@interface AMapRoadTrafficSearchResponse : AMapSearchObject
///路况信息
@property (nonatomic, strong) AMapTrafficInfo *trafficInfo;

@end

#pragma mark - AMapNearbySearchRequest
///附近搜索请求
@interface AMapNearbySearchRequest : AMapSearchObject
///中心点坐标
@property (nonatomic, copy)   AMapGeoPoint *center; 
///查询半径，范围：[0, 10000]，单位：米 [default = 1000]
@property (nonatomic, assign) NSInteger radius; 
///搜索距离类型，默认为直线距离
@property (nonatomic, assign) AMapNearbySearchType searchType; 
///检索时间范围，超过24小时的数据无法返回，范围[5, 24*60*60] 单位：秒 [default = 1800]
@property (nonatomic, assign) NSInteger timeRange; 
///返回条数，范围[1, 100], 默认30
@property (nonatomic, assign) NSInteger limit; 
@end

///附近搜索返回
@interface AMapNearbySearchResponse : AMapSearchObject
///结果总条数
@property (nonatomic, assign) NSInteger count; 
///周边用户信息 AMapNearbyUserInfo 数组
@property (nonatomic, strong) NSArray<AMapNearbyUserInfo *> *infos; 
@end

#pragma mark - AMapCloudSearchBaseRequest

///云图搜索请求基类
@interface AMapCloudSearchBaseRequest : AMapSearchObject
///要查询的表格ID, 必选
@property (nonatomic, copy) NSString *tableID;
///筛选条件数组, 可选, 对建立了排序筛选索引的字段进行筛选(系统默认为：_id，_name，_address，_updatetime，_createtime建立排序筛选索引).\n 说明：\n 1.支持对文本字段的精确匹配；支持对整数和小数字段的连续区间筛选;\n 2.示例:数组{"type:酒店", "star:[3,5]"}的含义,等同于SQL语句:WHERE type = "酒店" AND star BETWEEN 3 AND 5\n 注意: 所设置的过滤条件中不能含有&、#、%等URL的特殊符号。
@property (nonatomic, strong) NSArray<NSString *> *filter;
///排序字段名, 可选.\n 说明：\n 1.支持按建立了排序筛选索引的整数或小数字段进行排序：sortFields = "字段名"；\n 2.系统预设的字段(忽略sortType)：_distance：坐标与中心点距离升序排序，仅在周边检索时有效；_weight：权重降序排序，当存在keywords时有效；\n 3.默认值：当keywords存在时：默认按预设字段_weight排序；当keywords不存在时，默认按预设字段_distance排序；按建立了排序筛选索引的整数或小数字段进行排序时，若不填升降序，则默认按升序排列；
@property (nonatomic, copy) NSString *sortFields;
///可选, 排序方式(默认升序)
@property (nonatomic, assign) AMapCloudSortType sortType;
///可选, 每页记录数(每页最大记录数100, 默认20)
@property (nonatomic, assign) NSInteger offset;
///可选, 当前页数(>=1, 默认1)
@property (nonatomic, assign) NSInteger page;
@end

#pragma mark - AMapCloudPlaceAroundSearchRequest

///云图周边搜请求
@interface AMapCloudPOIAroundSearchRequest : AMapCloudSearchBaseRequest
///必填，中心点坐标。
@property (nonatomic, copy)   AMapGeoPoint *center;
///可选，查询半径（默认值为3000），单位：米。详细信息请参考：http://lbs.amap.com/yuntu/reference/cloudsearch/#t2
@property (nonatomic, assign) NSInteger     radius;
///可选，搜索关键词。\n 说明：\n 1. 请先在云图数据管理台添加或删除文本索引字段，系统默认为 _name 和 _address 建立文本索引；\n 2.支持关键字模糊检索，即对建立【文本索引字段】对应列内容进行模糊检索；如 keywords = “工商银行”，检索返回已建立文本索引列值中包含"工商"或者"银行"或者"工商银行"关键字的POI结果集。 \n 3. 支持关键字“或”精准检索，即对建立【文本索引字段】对应列内容进行多关键字检索；如 keywords = "招商银行|华夏银行|工商银行"，检索返回已建立索引列值中包含“招商银行”或者“华夏银行”或者“工商银行”的POI结果集，不会返回检索词切分后，如仅包含“招商”或者“银行”的POI集。 \n 4. 可赋值为空值，即 keywords = " " 表示空值； \n 5. 若 city = "城市名"，keywords = " " 或者 keywords = "关键字"，返回对应城市的全部数据或对应关键字的数据； \n 6. 一次请求最多返回2000条数据。\n 注意: 所设置的keywords中不能含有&、#、%等URL的特殊符号。
@property (nonatomic, copy) NSString *keywords;
@end

///云图polygon区域查询请求
@interface AMapCloudPOIPolygonSearchRequest : AMapCloudSearchBaseRequest
///必填，多边形。
@property (nonatomic, copy) AMapGeoPolygon *polygon;
///可选，搜索关键词。\n 说明：\n 1. 请先在云图数据管理台添加或删除文本索引字段，系统默认为 _name 和 _address 建立文本索引；\n 2.支持关键字模糊检索，即对建立【文本索引字段】对应列内容进行模糊检索；如 keywords = “工商银行”，检索返回已建立文本索引列值中包含“工商”或者“银行”或者“工商银行”关键字的POI结果集。\n 3. 支持关键字“或”精准检索，即对建立【文本索引字段】对应列内容进行多关键字检索；如 keywords = "招商银行|华夏银行|工商银行"，检索返回已建立索引列值中包含“招商银行”或者“华夏银行”或者“工商银行”的POI结果集，不会返回检索词切分后，如仅包含“招商”或者“银行”的POI集。\n 4. 可赋值为空值，即 keywords = " " 表示空值；\n 5. 若 city = "城市名"，keywords = " " 或者 keywords = "关键字"，返回对应城市的全部数据或对应关键字的数据；\n 6. 一次请求最多返回2000条数据。\n 注意: 所设置的keywords中不能含有&、#、%等URL的特殊符号。
@property (nonatomic, copy) NSString *keywords;
@end

///云图ID查询请求
@interface AMapCloudPOIIDSearchRequest : AMapCloudSearchBaseRequest
///必填,POI的ID
@property (nonatomic, assign) NSInteger uid; 
@end

///云图本地查询请求
@interface AMapCloudPOILocalSearchRequest : AMapCloudSearchBaseRequest
///必填，搜索关键词。\n 说明：\n 1. 请先在云图数据管理台添加或删除文本索引字段，系统默认为 _name 和 _address 建立文本索引；\n 2.支持关键字模糊检索，即对建立【文本索引字段】对应列内容进行模糊检索；如 keywords = "工商银行"，检索返回已建立文本索引列值中包含“工商”或者“银行”或者“工商银行”关键字的POI结果集。\n 3. 支持关键字“或”精准检索，即对建立【文本索引字段】对应列内容进行多关键字检索；如 keywords = "招商银行|华夏银行|工商银行"，检索返回已建立索引列值中包含“招商银行”或者“华夏银行”或者“工商银行”的POI结果集，不会返回检索词切分后，如仅包含“招商”或者“银行”的POI集。\n 4. 可赋值为空值，即 keywords = " " 表示空值；\n 5. 若 city = "城市名"，keywords = " " 或者 keywords = "关键字"，返回对应城市的全部数据或对应关键字的数据；\n 6. 一次请求最多返回2000条数据。 注意: 所设置的keywords中不能含有&、#、%等URL的特殊符号。
@property (nonatomic, copy) NSString *keywords;
///必填，城市名称\n 说明：\n 1. 支持全国/省/市/区县行政区划范围的检索；\n 2. city = "全国"，即对用户全表搜索；\n 3. 当city值设置非法或不正确时，按照 city = "全国"返回。
@property (nonatomic, copy) NSString *city; 
@end

///云图搜索返回
@interface AMapCloudPOISearchResponse : AMapSearchObject
///返回结果总数目
@property (nonatomic, assign) NSInteger  count; 
///返回的结果, AMapCloudPOI 数组
@property (nonatomic, strong) NSArray<AMapCloudPOI *>   *POIs; 

@end

#pragma mark - AMapShareSearchBaseRequest

///短串分享搜索请求基类, 请使用具体的子类。
@interface AMapShareSearchBaseRequest : AMapSearchObject
@end

///位置短串分享请求
@interface AMapLocationShareSearchRequest : AMapShareSearchBaseRequest
///必填, 位置坐标
@property (nonatomic, copy) AMapGeoPoint *location; 
///位置名称，请不要包含【,%&@#】等特殊符号
@property (nonatomic, copy) NSString     *name;
@end

///兴趣点短串分享请求
@interface AMapPOIShareSearchRequest : AMapShareSearchBaseRequest
///POI的ID，如果有ID则指定POI，否则按name查询。
@property (nonatomic, copy) NSString     *uid; 
///坐标
@property (nonatomic, copy) AMapGeoPoint *location; 
///名称，请不要包含【,%&@#】等特殊符号。
@property (nonatomic, copy) NSString     *name; 
///地址，请不要包含【,%&@#】等特殊符号。
@property (nonatomic, copy) NSString     *address; 
@end

///路径规划短串分享请求
@interface AMapRouteShareSearchRequest : AMapShareSearchBaseRequest
///默认为0\n 驾车:0-速度最快（时间）;\n 1-避免收费（不走收费路段的最快道路）;\n 2-距离优先;\n 3-不走高速;\n 4-结合实时交通（躲避拥堵）;\n 5-不走高速且避免收费;\n 6-不走高速且躲避拥堵;\n 7-躲避收费和拥堵;\n 8-不走高速且躲避收费和拥堵\n\n 公交:0-最快捷;\n 1-最经济;\n 2-最少换乘;\n 3-最少步行;\n 4-最舒适;\n 5-不乘地铁;\n\n 步行，无策略，均一样
@property (nonatomic, assign) NSInteger     strategy; 
///Route的type，默认为0，超出范围为0.\n 0为驾车，\n 1为公交，\n 2为步行
@property (nonatomic, assign) NSInteger     type;
///起点坐标
@property (nonatomic, copy)   AMapGeoPoint *startCoordinate; 
///终点坐标
@property (nonatomic, copy)   AMapGeoPoint *destinationCoordinate; 
///起点名称，默认为“已选择的位置”，请不要包含【,%&@#】等特殊符号
@property (nonatomic, copy)   NSString     *startName; 
///终点名称，默认为“已选择的位置”，请不要包含【,%&@#】等特殊符号
@property (nonatomic, copy)   NSString     *destinationName; 
@end

///导航短串分享请求
@interface AMapNavigationShareSearchRequest : AMapShareSearchBaseRequest

///默认为0，超出范围为0\n 驾车:0-速度最快（时间）;\n 1-避免收费（不走收费路段的最快道路）;\n 2-距离优先;\n 3-不走高速;\n 4-结合实时交通（躲避拥堵）;\n 5-不走高速且避免收费;\n 6-不走高速且躲避拥堵;\n 7-躲避收费和拥堵;\n 8-不走高速且躲避收费和拥堵
@property (nonatomic, assign) NSInteger     strategy; 
///起点坐标，若跳转到高德地图，默认更换为定位坐标
@property (nonatomic, copy)   AMapGeoPoint *startCoordinate; 
///终点坐标
@property (nonatomic, copy)   AMapGeoPoint *destinationCoordinate; 
@end

///导航短串分享响应
@interface AMapShareSearchResponse : AMapSearchObject
///转换后的短串
@property (nonatomic, copy) NSString *shareURL; 
@end
