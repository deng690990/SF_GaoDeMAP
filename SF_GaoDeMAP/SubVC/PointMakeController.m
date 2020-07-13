//
//  PointMakeController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/9/12.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "PointMakeController.h"
#import "MapManager.h"
@interface PointMakeController ()

@end

@implementation PointMakeController

- (void)viewDidLoad {
    [super viewDidLoad];
    //不管做什么地图操作都先定位自己的位置，不然后面会有一些bug（当然只是这个demo而言）
    [self locationOnlySelf];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithTitle:@"标注一点" style:UIBarButtonItemStylePlain target:self action:@selector(addAnonation)];
    self.navigationItem.rightBarButtonItem = rightItem;
}
//显示自己的定位信息
-(void)locationOnlySelf{
    MapManager *manager = [MapManager sharedManager];
    manager.controller = self;
    [manager initMapView];
}
//给一个坐标，在地图上显示大头针
-(void)addAnonation{
    CLLocationCoordinate2D coor;
    coor.latitude = 30.566666;
    coor.longitude = 104.054536;
    [[MapManager sharedManager] addAnomationWithCoor:coor];
}
@end
