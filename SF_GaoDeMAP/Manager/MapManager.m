//
//  MapManager.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/6/6.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "MapManager.h"
#import "SpeechSynthesizer.h"
#import "MoreMenuView.h"


#define SCREEN_W [UIScreen mainScreen].bounds.size.width
#define SCREEN_H [UIScreen mainScreen].bounds.size.height
@interface MapManager()<MAMapViewDelegate,AMapSearchDelegate,AMapNaviWalkManagerDelegate,AMapNaviWalkViewDelegate,AMapNaviDriveViewDelegate,AMapNaviDriveManagerDelegate,MoreMenuViewDelegate,AMapGeoFenceManagerDelegate>
@property (nonatomic,strong)NSMutableArray *searchResultArr;
@property (nonatomic, strong) MoreMenuView *moreMenu;//导航页面菜单选项
@end

static CLLocationCoordinate2D distinateCoor;//目的地坐标
@implementation MapManager

#pragma mark --创建一个单例类对象
+(instancetype)sharedManager{
    static MapManager *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        //初始化单例对象
        instance = [[MapManager alloc]init];
    });
    return instance;
}
#pragma mark --初始化地图对象
-(void)initMapView{
    [self initSearch];
    ///初始化地图
    _mapView = [[MAMapView alloc] initWithFrame:CGRectMake(0, 64, SCREEN_W      , SCREEN_H-64)];
    ///把地图添加至view
    [self.controller.view addSubview:_mapView];
    ///如果您需要进入地图就显示定位小蓝点，则需要下面两行代码
    _mapView.showsUserLocation = YES;
    _mapView.userTrackingMode = MAUserTrackingModeFollow;
    //设置地图缩放比例，即显示区域
    [_mapView setZoomLevel:15.1 animated:YES];
    _mapView.delegate = self;
    //设置定位精度
    _mapView.desiredAccuracy = kCLLocationAccuracyBest;
    //设置定位距离
    _mapView.distanceFilter = 5.0f;
    //把中心点设成自己的坐标
    _mapView.centerCoordinate = self.currentLocation.coordinate;
}
#pragma mark --带block的地图初始化方法
-(void)initMapViewWithBlock:(MapBlock)block{
    [self initSearch];
    ///初始化地图
    _mapView = [[MAMapView alloc] initWithFrame:self.controller.view.bounds];
    ///把地图添加至view
    [self.controller.view addSubview:_mapView];
    ///如果您需要进入地图就显示定位小蓝点，则需要下面两行代码
    _mapView.showsUserLocation = YES;
    _mapView.userTrackingMode = MAUserTrackingModeFollow;
    //设置地图缩放比例，即显示区域
    [_mapView setZoomLevel:15.1 animated:YES];
    _mapView.delegate = self;
    //设置定位精度
    _mapView.desiredAccuracy = kCLLocationAccuracyBest;
    //设置定位距离
    _mapView.distanceFilter = 5.0f;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        block();
    });
}
#pragma mark --初始化导航管理类对象
- (void)initWalkManager
{
    if (self.walkManager == nil)
    {
        self.walkManager = [[AMapNaviWalkManager alloc] init];
        [self.walkManager setDelegate:self];
    }
}
#pragma mark --初始化导航管理类对象
- (void)initDriveManager
{
    if (self.driveManager == nil)
    {
        self.driveManager = [AMapNaviDriveManager sharedInstance];
        [self.driveManager setDelegate:self];
    }
}
#pragma mark --标记添加大头针
-(void)addAnomationWithCoor:(CLLocationCoordinate2D)coor{
    //地理坐标反编码为文字
    AMapReGeocodeSearchRequest *request =[[AMapReGeocodeSearchRequest alloc] init];
    request.location =[AMapGeoPoint locationWithLatitude:coor.latitude longitude:coor.longitude];
    [_search AMapReGoecodeSearch:request];
    _anomationPoint = [[MAPointAnnotation alloc]init];
    _anomationPoint.coordinate = coor;
    [self.mapView addAnnotation:_anomationPoint];
    //将标记点的位置放在地图的中心
    _mapView.centerCoordinate = coor;
}
#pragma mark --设置大头针上方气泡的内容的代理方法
-(MAAnnotationView *)mapView:(MAMapView *)mapView viewForAnnotation:(id<MAAnnotation>)annotation{
    //大头针标注
    if ([annotation isKindOfClass:[MAUserLocation class]]) {
        return nil;
    }else{
        static NSString *pointReuseIndentifier = @"pointReuseIndentifier";
        MAAnnotationView*annotationView = (MAAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:pointReuseIndentifier];
        if (annotationView == nil) {
            annotationView = [[MAAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:pointReuseIndentifier];
        }
        annotationView.frame = CGRectMake(0, 0, 100, 100);
        annotationView.canShowCallout= YES;       //设置气泡可以弹出，默认为NO
        //annotationView.animatesDrop = YES;        //设置标注动画显示，默认为NO
        annotationView.draggable = YES;           //设置标注可以拖动，默认为NO
        //        annotationView.pinColor = MAPinAnnotationColorPurple;
        
        //设置大头针显示的图片
        if (!self.locationPointImgName) {
            annotationView.image = [UIImage imageNamed:@"定位"];
        }else{
            annotationView.image = [UIImage imageNamed:self.locationPointImgName];
        }
        //点击大头针显示的左边的视图
        UIImageView *imageV = [[UIImageView alloc]init];
        if (!self.destinationImgName) {
            imageV.image = [UIImage imageNamed:@"目的地"];
        }else{
            imageV.image = [UIImage imageNamed:self.destinationImgName];
        }
        annotationView.leftCalloutAccessoryView = imageV;
//        点击大头针显示的右边视图
        UIButton *rightButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
        rightButton.backgroundColor = [UIColor grayColor];
        [rightButton setTitle:@"导航" forState:UIControlStateNormal];
        [rightButton addTarget:self action:@selector(navBtnClick) forControlEvents:UIControlEventTouchUpInside];
        annotationView.rightCalloutAccessoryView = rightButton;
        return annotationView;
    }
}
#pragma mark --导航点击事件
-(void)navBtnClick{
    self.controller.navigationController.navigationBar.hidden = YES;
    NSLog(@"%lf---%lf",distinateCoor.latitude,distinateCoor.longitude);
    //初始化起点和终点
    self.startPoint = [AMapNaviPoint locationWithLatitude:_currentLocation.coordinate.latitude longitude:_currentLocation.coordinate.longitude];
    self.endPoint   = [AMapNaviPoint locationWithLatitude:distinateCoor.latitude longitude:distinateCoor.longitude];
    [self initDriveManager];
    self.driveView = [[AMapNaviDriveView alloc] init];
    self.driveView.frame = self.controller.view.frame;
    self.driveView.delegate = self;
    [self.controller.view addSubview:self.driveView];
    [self.driveManager addDataRepresentative:self.driveView];
    [self.driveManager calculateDriveRouteWithStartPoints:@[self.startPoint] endPoints:@[self.endPoint]wayPoints:nil drivingStrategy:AMapNaviDrivingStrategySingleDefault];
}

#pragma mark serach初始化
-(void)initSearch{
    _search =[[AMapSearchAPI alloc] init];
    _search.delegate=self;
}
#pragma mark --初始化导航菜单键
- (void)initMoreMenu
{
    if (self.moreMenu == nil)
    {
        self.moreMenu = [[MoreMenuView alloc] init];
        self.moreMenu.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
        
        [self.moreMenu setDelegate:self];
    }
}

#pragma mark --地图纠偏
-(CLLocationCoordinate2D)currectGpsWithLocation:(CLLocationCoordinate2D)coor{
    CLLocationCoordinate2D gcjPt = [JZLocationConverter wgs84ToGcj02:coor];
    NSLog(@"%lf,%lf",gcjPt.latitude,gcjPt.longitude);
    return gcjPt;
}
#pragma mark 搜索请求发起后的回调,用于标记自己当前的位置
/**失败回调*/
-(void)AMapSearchRequest:(id)request didFailWithError:(NSError *)error{
    
    NSLog(@"request: %@------error:  %@",request,error);
}
//*成功回调
-(void)onReGeocodeSearchDone:(AMapReGeocodeSearchRequest *)request response:(AMapReGeocodeSearchResponse *)response{
    //我们把编码后的地理位置，显示到 大头针的标题和子标题上
    NSString *title =response.regeocode.addressComponent.city;
    NSLog(@"%@",title);
    if (title.length == 0) {
        title = response.regeocode.addressComponent.province;
    }
    //    NSLog(@"=====%@",request.location);
    if (request.location.latitude == _currentLocation.coordinate.latitude&&request.location.longitude == _currentLocation.coordinate.longitude) {
        _mapView.userLocation.title = title;
        _mapView.userLocation.subtitle = response.regeocode.formattedAddress;
    }else{
        self.anomationPoint.title = title;
        self.anomationPoint.subtitle = response.regeocode.formattedAddress;
    }
}
#pragma mark 定位更新回调
-(void)mapView:(MAMapView *)mapView didUpdateUserLocation:(MAUserLocation *)userLocation
updatingLocation:(BOOL)updatingLocation
{
    if(updatingLocation)
    {
        self.currentLocation = [userLocation.location copy];
    }
    
    
}
-(void)setCurrentLocation:(CLLocation *)currentLocation{
    
    if (!_currentLocation) {
        _currentLocation = currentLocation;
        _mapView.centerCoordinate = currentLocation.coordinate;
        [self reGeoCoding];
        if (self.geoBlock) {
            _mapView.centerCoordinate = self.config.centerCoordinate;
            self.geoBlock();
        }
    }
}
#pragma mark 逆地理编码,经纬度编码成地址
-(void)reGeoCoding{
    if (_currentLocation) {
        AMapReGeocodeSearchRequest *request =[[AMapReGeocodeSearchRequest alloc] init];
        request.location =[AMapGeoPoint locationWithLatitude:_currentLocation.coordinate.latitude longitude:_currentLocation.coordinate.longitude];
        [_search AMapReGoecodeSearch:request];
    }
}
#pragma mark --地址编码成经纬度
-(void)GeocodingWithAddress:(NSString *)address{
    AMapGeocodeSearchRequest *request = [[AMapGeocodeSearchRequest alloc]init];
    request.address = address;
    [_search AMapGeocodeSearch:request];
}
#pragma mark --地址编码回调
-(void)onGeocodeSearchDone:(AMapGeocodeSearchRequest *)request response:(AMapGeocodeSearchResponse *)response{
    AMapGeoPoint *point = response.geocodes[0].location;
    NSLog(@"----%lf====%lf",point.latitude,point.latitude);
}
#pragma mark --选中某个大头针后回调的方法
-(void)mapView:(MAMapView *)mapView didSelectAnnotationView:(MAAnnotationView *)view{
    //    NSLog(@"%lf------%lf",view.annotation.coordinate.latitude,view.annotation.coordinate.longitude);
    distinateCoor = view.annotation.coordinate;
}
#pragma mark --步行导航代理方法
-(void)walkManagerOnCalculateRouteSuccess:(AMapNaviWalkManager *)walkManager{
    [walkManager startGPSNavi];
}
#pragma mark --关闭导航的方法
-(void)walkViewCloseButtonClicked:(AMapNaviWalkView *)walkView{
    self.controller.navigationController.navigationBar.hidden = NO;
    [self.walkManager stopNavi];
    [walkView removeFromSuperview];
    //停止语音
    [[SpeechSynthesizer sharedSpeechSynthesizer] stopSpeak];
}
#pragma mark --行车导航回调
-(void)driveManagerOnCalculateRouteSuccess:(AMapNaviDriveManager *)driveManager{
    [self initMoreMenu];
    //将driveView添加为导航数据的Representative，使其可以接收到导航诱导数据
    [self.driveManager addDataRepresentative:self.driveView];
    [driveManager startGPSNavi];
}
-(void)driveViewCloseButtonClicked:(AMapNaviDriveView *)driveView{
    self.controller.navigationController.navigationBar.hidden = NO;
    [self.driveManager stopNavi];
    [driveView removeFromSuperview];
    //停止语音
    [[SpeechSynthesizer sharedSpeechSynthesizer] stopSpeak];
}
- (BOOL)driveManagerIsNaviSoundPlaying:(AMapNaviDriveManager *)driveManager
{
    return [[SpeechSynthesizer sharedSpeechSynthesizer] isSpeaking];
}
- (void)driveManager:(AMapNaviDriveManager *)driveManager playNaviSoundString:(NSString *)soundString soundStringType:(AMapNaviSoundType)soundStringType
{
    NSLog(@"playNaviSoundString:{%ld:%@}", (long)soundStringType, soundString);
    
    [[SpeechSynthesizer sharedSpeechSynthesizer] speakString:soundString];
}
- (void)driveViewMoreButtonClicked:(AMapNaviDriveView *)driveView
{
    //配置MoreMenu状态
    [self.moreMenu setTrackingMode:self.driveView.trackingMode];
    [self.moreMenu setShowNightType:self.driveView.mapViewModeType];
    
    [self.moreMenu setFrame:self.controller.view.bounds];
    [self.controller.view addSubview:self.moreMenu];
}
- (void)driveViewTrunIndicatorViewTapped:(AMapNaviDriveView *)driveView
{
    if (self.driveView.showMode == AMapNaviDriveViewShowModeCarPositionLocked)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeNormal];
    }
    else if (self.driveView.showMode == AMapNaviDriveViewShowModeNormal)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeOverview];
    }
    else if (self.driveView.showMode == AMapNaviDriveViewShowModeOverview)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeCarPositionLocked];
    }
}
- (void)driveView:(AMapNaviDriveView *)driveView didChangeShowMode:(AMapNaviDriveViewShowMode)showMode
{
    NSLog(@"didChangeShowMode:%ld", (long)showMode);
}
#pragma mark --周边搜索方法
-(void)searchAroundWithKeyWords:(NSString *)keywords{
    if (_currentLocation==nil||_search==nil) {
        NSLog(@"location = %@---search=%@",_currentLocation,_search);
        NSLog(@"搜索失败,定位或搜索对象未初始化");
        return;
    }
    AMapPOIAroundSearchRequest  *request=[[AMapPOIAroundSearchRequest alloc] init];
    //设置搜索范围，以显示在地图上
    request.radius = 10000;
    request.location=[AMapGeoPoint locationWithLatitude:_currentLocation.coordinate.latitude longitude:_currentLocation.coordinate.longitude];
    request.keywords = keywords;
    [_search AMapPOIAroundSearch:request];
}
#pragma mark 周边搜索回调
-(void)onPOISearchDone:(AMapPOISearchBaseRequest *)request response:(AMapPOISearchResponse *)response{
    
    if (response.pois.count>0) {
        
        self.searchResultArr = [response.pois mutableCopy];
        //        NSLog(@"%@",self.dataArray);
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [self setupPointAnotation:self.searchResultArr];
            
        });
    }else{
        NSLog(@"搜索失败，附近暂无搜索内容");
    }
}
#pragma mark --构造折线数据对象
-(void)drawLineWithArray:(NSArray *)array{
    //    //构造折线数据对象
    CLLocationCoordinate2D commonPolylineCoords[array.count];
    for (int i = 0; i<array.count; i++) {
        NSString *location = array[i];
        commonPolylineCoords[i].latitude = [location substringToIndex:9].floatValue;
        commonPolylineCoords[i].longitude = [location substringFromIndex:10].floatValue;
    }
    //构造折线对象
    MAPolyline *commonPolyline = [MAPolyline polylineWithCoordinates:commonPolylineCoords count:array.count];
    
    //在地图上添加折线对象
    [_mapView addOverlay: commonPolyline];
    //将地图的中心点设为固定的点
    _mapView.centerCoordinate = commonPolylineCoords[array.count/2];
    
}
#pragma mark --标记转折点的位置(轨迹回放)
-(void)addAnomationWithArray:(NSArray *)array{
    for (int i = 0; i < array.count; i++) {
        CLLocationCoordinate2D coor;
        coor.latitude = [array[i] substringToIndex:9].floatValue;
        coor.longitude = [array[i] substringFromIndex:10].floatValue;
        MAPointAnnotation *coorPoint = [[MAPointAnnotation alloc]init];
        coorPoint.coordinate = coor;
        coorPoint.title = [NSString stringWithFormat:@"位置%d",i+1];
        [self.mapView addAnnotation:coorPoint];
    }
}
#pragma mark --设置图层代理方法
- (MAOverlayRenderer *)mapView:(MAMapView *)mapView rendererForOverlay:(id <MAOverlay>)overlay
{
    //图层为折线
    if ([overlay isKindOfClass:[MAPolyline class]])
    {
        MAPolylineRenderer *polylineRenderer = [[MAPolylineRenderer alloc] initWithPolyline:overlay];
        
        polylineRenderer.lineWidth    = 12.f;
        //设置轨迹颜色
        //        polylineRenderer.strokeColor  = [UIColor colorWithRed:0 green:1 blue:0 alpha:0.6];
        polylineRenderer.lineJoinType = kMALineJoinRound;
        polylineRenderer.lineCapType  = kMALineCapRound;
        //将轨迹设置为自定义的样式
        polylineRenderer.strokeImage = [UIImage imageNamed:@"map_history"];
        
        return polylineRenderer;
    }
    //图层为圆形
    if ([overlay isKindOfClass:[MACircle class]]) {
        MACircleRenderer * polygonRenderer = [[MACircleRenderer alloc]initWithCircle:overlay];
        polygonRenderer.lineWidth   = self.config.geoLineW;
         polygonRenderer.strokeColor = self.config.geoColor;
        polygonRenderer.fillColor = [UIColor colorWithRed:0.73 green:0.73 blue:0.73 alpha:0.2];
        return polygonRenderer;
    }
    // 多边形地理围栏
    if ([overlay isKindOfClass:[MAPolygon class]]) {
        MAPolygonRenderer *polylineRenderer = [[MAPolygonRenderer alloc] initWithPolygon:(MAPolygon *)overlay];
        polylineRenderer.lineWidth = self.config.geoLineW;
        polylineRenderer.strokeColor = self.config.geoColor;
        //内部填充色
        polylineRenderer.fillColor = [UIColor   colorWithRed:113/255.0 green:174/255.0 blue:247/255.0 alpha:0.3];
        return polylineRenderer;
    }
    return nil;
}

#pragma mark --搜索附近成功后设置大头针
-(void)setupPointAnotation:(NSMutableArray *)array{
    [_mapView setZoomLevel:13.1 animated:YES];
    for (int i = 0; i < array.count; i++) {
        CLLocationCoordinate2D coor;
        AMapPOI *poi = self.searchResultArr[i];
        coor.latitude = poi.location.latitude;
        coor.longitude = poi.location.longitude;
        MAPointAnnotation *point = [[MAPointAnnotation alloc]init];
        point.coordinate = coor;
        point.title = poi.name;
        [self.mapView addAnnotation:point];
    }
    //把中心点设成自己的坐标
    self.mapView.centerCoordinate = self.currentLocation.coordinate;
}
#pragma mark - MoreMenu Delegate

- (void)moreMenuViewFinishButtonClicked
{
    [self.moreMenu removeFromSuperview];
}

- (void)moreMenuViewNightTypeChangeTo:(BOOL)isShowNightType
{
    self.driveView.mapViewModeType = isShowNightType;
}

- (void)moreMenuViewTrackingModeChangeTo:(AMapNaviViewTrackingMode)trackingMode
{
    [self.driveView setTrackingMode:trackingMode];
}
#pragma mark --围栏地图初始化方法
-(void)initMapViewWithGeofraphyBlock:(MapBlock)block{
    [self initSearch];
    ///初始化地图
    _mapView = [[MAMapView alloc] initWithFrame:self.controller.view.bounds];
    ///把地图添加至view
    [self.controller.view addSubview:_mapView];
    ///如果您需要进入地图就显示定位小蓝点，则需要下面两行代码
    _mapView.showsUserLocation = YES;
    _mapView.userTrackingMode = MAUserTrackingModeFollow;
    //设置地图缩放比例，即显示区域
    [_mapView setZoomLevel:15.1 animated:YES];
    _mapView.delegate = self;
    //设置定位精度
    _mapView.desiredAccuracy = kCLLocationAccuracyBest;
    //设置定位距离
    _mapView.distanceFilter = 5.0f;
    self.geoBlock = block;
}
#pragma mark --地理围栏部分
-(AMapGeoFenceManager *)geoFenceManager{
    if (!_geoFenceManager) {
        _geoFenceManager = [[AMapGeoFenceManager alloc] init];
        _geoFenceManager.delegate = self;
        //设置希望侦测的围栏触发行为，默认是侦测用户进入围栏的行为，即AMapGeoFenceActiveActionInside |AMapGeoFenceActiveActionOutside | AMapGeoFenceActiveActionStayed，这边设置为进入，离开，停留（在围栏内10分钟以上），都触发回调
        _geoFenceManager.activeAction = AMapGeoFenceActiveActionInside;
        _geoFenceManager.allowsBackgroundLocationUpdates = YES;  //允许后台定位
    }
    return _geoFenceManager;
}

/**
 创建围栏的方法
 */
-(void)creadGeofenceWithGeoId:(NSString *)customID{
    if (_config.geoType == GeoType_circle) {
        [self.geoFenceManager addCircleRegionForMonitoringWithCenter:self.config.centerCoordinate radius:self.config.reduis customID:customID];
    }else if (_config.geoType == GeoType_polygon){
        [self.geoFenceManager addPolygonRegionForMonitoringWithCoordinates:self.config.coordinates count:self.config.coordinateCount customID:customID];
    }
}
//围栏代理方法
- (void)amapGeoFenceManager:(AMapGeoFenceManager *)manager didAddRegionForMonitoringFinished:(NSArray<AMapGeoFenceRegion *> *)regions customID:(NSString *)customID error:(NSError *)error {
    if (error) {
        NSLog(@"围栏创建失败 %@",error);
    } else {
        NSLog(@"围栏创建成功");
        //围栏创建成功画边界
        if (self.config.geoType == GeoType_circle) {
            //圆形
            MACircle *circle = [self showCircleInMap:self.config.centerCoordinate radius:self.config.reduis];
            [self.mapView setVisibleMapRect:circle.boundingMapRect edgePadding:UIEdgeInsetsMake(20, 20, 20, 20) animated:NO];
        }else if(self.config.geoType == GeoType_polygon){
            AMapGeoFencePolygonRegion *polygonRegion = (AMapGeoFencePolygonRegion *)regions.firstObject;
            MAPolygon *polygonOverlay = [self showPolygonInMap:polygonRegion.coordinates count:polygonRegion.count];
            [self.mapView setVisibleMapRect:polygonOverlay.boundingMapRect edgePadding:UIEdgeInsetsMake(20, 20, 20, 20) animated:NO];
        }
    }
}
//地图上显示圆
- (MACircle *)showCircleInMap:(CLLocationCoordinate2D )coordinate radius:(NSInteger)radius {
    MACircle *circleOverlay = [MACircle circleWithCenterCoordinate:coordinate radius:radius];
    [self.mapView addOverlay:circleOverlay];
    return circleOverlay;
}
#pragma mark 地图上显示多边形
- (MAPolygon *)showPolygonInMap:(CLLocationCoordinate2D *)coordinates count:(NSInteger)count {
    MAPolygon *polygonOverlay = [MAPolygon polygonWithCoordinates:coordinates count:count];
    [self.mapView addOverlay:polygonOverlay];
    return polygonOverlay;
}
- (void)amapGeoFenceManager:(AMapGeoFenceManager *)manager didGeoFencesStatusChangedForRegion:(AMapGeoFenceRegion *)region customID:(NSString *)customID error:(NSError *)error {
    if (error) {
        NSLog(@"围栏状态变化错误 %@",error);
    }else{
        NSLog(@"用户超出了围栏范围 %@",[region description]);
    }
}
@end
