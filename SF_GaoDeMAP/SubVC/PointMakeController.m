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
-(void)dealloc{
    NSLog(@"%s",__FUNCTION__);
    // 防止内存泄漏
    [[MapManager sharedManager] removeMapView];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    [[MapManager sharedManager] initMapView];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithTitle:@"标注一点" style:UIBarButtonItemStylePlain target:self action:@selector(addAnonation)];
    self.navigationItem.rightBarButtonItem = rightItem;
}

//给一个坐标，在地图上显示大头针
-(void)addAnonation{
    CLLocationCoordinate2D coor;
    coor.latitude = 30.566666;
    coor.longitude = 104.054536;
    [[MapManager sharedManager] addAnomationWithCoor:coor];
}
@end
