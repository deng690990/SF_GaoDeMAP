//
//  Track3DAnimationVc.m
//  SF_GaoDeMAP
//
//  Created by 邓升发 on 2020/7/13.
//  Copyright © 2020 ShouNew.com. All rights reserved.
//

#import "Track3DAnimationVc.h"
#import "MapManager.h"
@interface Track3DAnimationVc ()<MAMapViewDelegate>
///
@property (nonatomic, strong) MAAnimatedAnnotation *myLocation;
/// 地图
@property (nonatomic, strong) MAMapView *mapView;
/// 定时器
@property (nonatomic, strong) CADisplayLink *dpLink;
/// 更新的次数
@property (nonatomic, assign) NSInteger uptateIndex;
/// 角度值
@property (nonatomic, assign) CGFloat yvAngle;
/// 轨迹线路对象
@property (nonatomic, strong) MAPolyline *polyline;
/// CLLocationCoordinate2D 点数组，用于绘制轨迹
@property (nonatomic, strong) NSMutableArray *traceCoordinates;
/// 临时数组 暂存坐标
@property (nonatomic, strong) NSMutableArray *temporarytraceCoordinates;
@end

@implementation Track3DAnimationVc

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupMapView];
    
}
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self start];
}
-(void)setupMapView{
    _mapView = [[MAMapView alloc] initWithFrame:self.view.bounds];
    _mapView.delegate = self;
    _mapView.showsCompass = NO;
    _mapView.showsScale = NO;
    _mapView.mapType = MAMapTypeSatellite;
    
    //JSON文件的路径
    NSString *path = [[NSBundle mainBundle] pathForResource:@"running_record.json" ofType:nil];
    //加载JSON文件
    NSData *data = [NSData dataWithContentsOfFile:path];
    //将JSON数据转为NSArray或NSDictionary
    NSArray *dictArray = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
    for (NSDictionary *dic in dictArray) {
        CLLocation *location = [[CLLocation alloc] initWithLatitude:[dic[@"latitude"] floatValue] longitude:[dic[@"longtitude"] floatValue]];
        [self.traceCoordinates addObject:location];
    }
    CLLocation *firstLocation = self.traceCoordinates.firstObject;
    _mapView.centerCoordinate = firstLocation.coordinate;
    [_mapView setZoomLevel:18 animated:YES];
    [self.view addSubview:_mapView];
}
-(void)start{
    self.uptateIndex = 0;
    self.yvAngle = 0;
    [self.temporarytraceCoordinates removeAllObjects];
    [self.mapView setZoomLevel:18 animated:YES];
    self.dpLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    self.dpLink.paused = NO;
    ///最小刷新时间 (帧)
    self.dpLink.frameInterval = 1;
    [self.dpLink addToRunLoop:NSRunLoop.currentRunLoop forMode:NSDefaultRunLoopMode];
    
}
-(void)update{
    if (self.uptateIndex > self.traceCoordinates.count - 2) {
        [UIView animateWithDuration:2.0 animations:^{
            if (_polyline) {
                [self.mapView showOverlays:@[_polyline] edgePadding:UIEdgeInsetsMake(120, 20, 240, 20) animated:YES];
            }
            self.dpLink.paused = YES;
            [self.dpLink removeFromRunLoop:NSRunLoop.currentRunLoop forMode:NSDefaultRunLoopMode];
            [self.dpLink invalidate];
            self.dpLink = nil;
        }];
        return;
    }else{
        if (_polyline) {
            [self.mapView removeOverlay:_polyline];
        }
        [self.temporarytraceCoordinates addObject:self.traceCoordinates[self.uptateIndex]];
        CLLocationCoordinate2D commonPolylineCoords[self.temporarytraceCoordinates.count];
        for (int i = 0; i < self.temporarytraceCoordinates.count; i++) {
            CLLocation *location = self.temporarytraceCoordinates[i];
            commonPolylineCoords[i].latitude = location.coordinate.latitude;
            commonPolylineCoords[i].longitude = location.coordinate.longitude;
        }
        self.polyline = [MAPolyline polylineWithCoordinates:commonPolylineCoords count:self.temporarytraceCoordinates.count];
        CLLocation *lastLocation = self.temporarytraceCoordinates.lastObject;
        if (!self.myLocation) {
            self.myLocation = [[MAAnimatedAnnotation alloc] init];
            self.myLocation.title = @"AMap";
            self.myLocation.coordinate = CLLocationCoordinate2DMake(lastLocation.coordinate.latitude, lastLocation.coordinate.longitude);
            [self.mapView addAnnotation:self.myLocation];
        }
        self.myLocation.coordinate = CLLocationCoordinate2DMake(lastLocation.coordinate.latitude, lastLocation.coordinate.longitude);
        [self.mapView addOverlay:self.polyline];
        [self.mapView setCenterCoordinate:((CLLocation *)self.traceCoordinates[self.uptateIndex+1]).coordinate animated:NO];
        [self.mapView setRotationDegree:self.yvAngle animated:NO duration:1];
        [self.mapView setCameraDegree:self.yvAngle animated:NO duration:1];
        self.yvAngle += 1;
        self.uptateIndex += 1;
    }
}
-(MAOverlayRenderer *)mapView:(MAMapView *)mapView rendererForOverlay:(id<MAOverlay>)overlay{
    if ([overlay isKindOfClass:[MAPolyline class]]) {
        MAPolylineRenderer *render = [[MAPolylineRenderer alloc] initWithOverlay:overlay];
        render.lineWidth = 8.0;
        render.strokeColor = [UIColor colorWithRed:0 green:230 blue:239 alpha:1];
        return render;
    }
    return nil;
}
#pragma mark --设置头像大头针
-(MAAnnotationView *)mapView:(MAMapView *)mapView viewForAnnotation:(id<MAAnnotation>)annotation{
    if ([annotation isEqual:self.myLocation]) {
        static NSString *pointReuseIndentifier = @"myLcoationIdentifier";
        MAAnnotationView*annotationView = (MAAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:pointReuseIndentifier];
        if (annotationView == nil) {
            annotationView = [[MAAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:pointReuseIndentifier];
        }
        annotationView.image = [UIImage imageNamed:@"userHeadimage"];
        annotationView.imageView.layer.cornerRadius = 20;
        annotationView.imageView.layer.masksToBounds = YES;
        annotationView.imageView.backgroundColor = UIColor.whiteColor;
        annotationView.imageView.layer.borderColor = UIColor.whiteColor.CGColor;
        annotationView.imageView.layer.borderWidth = 2;
        annotationView.canShowCallout = NO;
        return annotationView;
    }
    return nil;
}
#pragma mark - 懒加载
-(NSMutableArray *)traceCoordinates{
    if (!_traceCoordinates) {
        _traceCoordinates = [NSMutableArray array];
    }
    return _traceCoordinates;
}
-(NSMutableArray *)temporarytraceCoordinates{
    if (!_temporarytraceCoordinates) {
        _temporarytraceCoordinates = [NSMutableArray array];
    }
    return _temporarytraceCoordinates;
}
@end
