//
//  TrackViewController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/6/9.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "TrackViewController.h"
#import "MapManager.h"
@interface TrackViewController ()

@end
@implementation TrackViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"轨迹绘制";
    MapManager *manager = [MapManager sharedManager];
    manager.controller = self;
    [manager initMapView];
    [manager.mapView setZoomLevel:13.1 animated:YES];
    NSArray *array = @[@"39.822136,116.35095",@"39.832136,116.42095",@"39.902136,116.42095",@"39.902136,116.44095"];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [manager drawLineWithArray:array];
        [manager addAnomationWithArray:@[@"39.822136,116.35095",@"39.902136,116.44095"]];
    });
}

@end
