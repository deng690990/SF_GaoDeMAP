//
//  MapViewController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/9/12.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "MapViewController.h"
#import "MapManager.h"

@interface MapViewController ()

@end

@implementation MapViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"地图页面";
    //不管做什么地图操作都先定位自己的位置，不然后面会有一些bug（当然只是这个demo而言）
    [self locationOnlySelf];
}
//显示自己的定位信息
-(void)locationOnlySelf{
    MapManager *manager = [MapManager sharedManager];
    manager.controller = self;
    [manager initMapView];
}

@end
