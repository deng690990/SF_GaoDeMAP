//
//  ViewController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/6/6.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "ViewController.h"
#import "MapManager.h"
#import "TrackViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //不管进行什么地图操作都要先定位自己位置
    [self locationOnlySelf];
    
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
//附近搜索
-(void)searchAround{
    //设置了图片就用设置的图片，没有设置图片就用默认图片
//    [MapManager sharedManager].destinationImgName = @"首牛";
//    [MapManager sharedManager].locationPointImgName = @"首牛";
    [[MapManager sharedManager] searchAroundWithKeyWords:@"景点"];
}
//轨迹回放
-(void)trackLook{
    TrackViewController *VC = [[TrackViewController alloc]init];
    [self presentViewController:VC animated:YES completion:nil];
}
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
//    [self trackLook];
    //搜索附近
    [self searchAround];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}


@end
