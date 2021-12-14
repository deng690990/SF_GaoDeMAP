//
//  SearchViewController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/9/12.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "SearchViewController.h"
#import "MapManager.h"
@interface SearchViewController ()

@end

@implementation SearchViewController

-(void)dealloc{
    NSLog(@"%s",__FUNCTION__);
    // 防止内存泄漏
    [[MapManager sharedManager] removeMapView];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    [[MapManager sharedManager] initMapView];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithTitle:@"附近搜索" style:UIBarButtonItemStylePlain target:self action:@selector(searchAround)];
    self.navigationItem.rightBarButtonItem = rightItem;
}

//附近搜索
-(void)searchAround{
    //设置了图片就用设置的图片，没有设置图片就用默认图片
    //        [MapManager sharedManager].destinationImgName = @"首牛";
    //        [MapManager sharedManager].locationPointImgName = @"首牛";
    [[MapManager sharedManager] searchAroundWithKeyWords:@"景点"];
}
@end
