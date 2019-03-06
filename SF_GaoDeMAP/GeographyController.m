//
//  GeographyController.m
//  SF_GaoDeMAP
//
//  Created by 邓升发 on 2019/2/27.
//  Copyright © 2019年 ShouNew.com. All rights reserved.
//

#import "GeographyController.h"
#import "MapManager.h"
@interface GeographyController ()
@property (nonatomic,strong) MapManager *manager;
@end

@implementation GeographyController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"地理围栏";
    self.view.backgroundColor = [UIColor whiteColor];
    
    
    [self mapMethod];
}
-(void)mapMethod{
    _manager = [MapManager sharedManager];
    _manager.controller = self;
    //圆形
//    GeographyConfigModel *configModel = [GeographyConfigModel new];
//    configModel.geoType = GeoType_circle;
//    configModel.geoColor = [UIColor redColor];
//    configModel.geoLineW = 3.0;
//    configModel.reduis = 300;
//    manager.config = configModel;
//    [manager initMapViewWithGeofraphyBlock:^{
//        //假如要以自己的定位为中心点就写在block里面，假如不是，最好写在外面
//        configModel.centerCoordinate = manager.currentLocation.coordinate;
//        //创建围栏
//        [manager creadGeofenceWithGeoId:@"circleId"];
//    }];
    //多边形
    NSInteger count = 4;
    CLLocationCoordinate2D *coorArr = malloc(sizeof(CLLocationCoordinate2D) * count);
    coorArr[0] = CLLocationCoordinate2DMake(39.933921, 116.372927);     //平安里地铁站
    coorArr[1] = CLLocationCoordinate2DMake(39.907261, 116.376532);     //西单地铁站
    coorArr[2] = CLLocationCoordinate2DMake(39.900611, 116.418161);     //崇文门地铁站
    coorArr[3] = CLLocationCoordinate2DMake(39.941949, 116.435497);     //东直门地铁站
    GeographyConfigModel *configModel = [GeographyConfigModel new];
    configModel.geoType = GeoType_polygon;
    configModel.geoColor = [UIColor redColor];
    configModel.geoLineW = 3.0;
    configModel.coordinates = coorArr;
    configModel.coordinateCount = count;
    //以多边形任意一角作为地图的中心点
    configModel.centerCoordinate = CLLocationCoordinate2DMake(39.941949, 116.435497);
    _manager.config = configModel;
    [_manager initMapViewWithGeofraphyBlock:^{
        //创建围栏
        [_manager creadGeofenceWithGeoId:@"circleId"];
    }];
}
- (void)viewDidDisappear:(BOOL)animated{
    //移除所有围栏
    [_manager.geoFenceManager removeAllGeoFenceRegions];
}
@end
