//
//  ViewController.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/6/6.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "ViewController.h"
#import "MapViewController.h"
#import "PointMakeController.h"
#import "SearchViewController.h"
#import "MapManager.h"
#import "TrackViewController.h"
#import "GeographyController.h"

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupUI];
}
-(void)setupUI{
    UITableView *tableView = [[UITableView alloc]initWithFrame:self.view.bounds];
    tableView.delegate = self;
    tableView.dataSource = self;
    tableView.rowHeight = 70;
    [self.view addSubview:tableView];
    
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"cell"];
    }
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    if (indexPath.row == 0) {
        cell.textLabel.text = @"定位当前位置";
    }else if (indexPath.row == 1){
        cell.textLabel.text = @"标记地图上某点";
    }else if (indexPath.row == 2){
        cell.textLabel.text = @"附近搜索";
    }else if (indexPath.row == 3){
        cell.textLabel.text = @"绘制轨迹";
    }else if (indexPath.row == 4){
        cell.textLabel.text = @"地理围栏";
    }
    return cell;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return 5;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.row == 0) {
        MapViewController *MapVc = [[MapViewController alloc]init];
        [self.navigationController pushViewController:MapVc animated:YES];
    }else if(indexPath.row == 1){
        PointMakeController *pointVc = [[PointMakeController alloc]init];
        [self.navigationController pushViewController:pointVc animated:YES];
    }else if(indexPath.row == 2){
        SearchViewController *searchVc = [[SearchViewController alloc]init];
        [self.navigationController pushViewController:searchVc animated:YES];
    }else if(indexPath.row == 3){
        TrackViewController *VC = [[TrackViewController alloc]init];
        [self.navigationController pushViewController:VC animated:YES];
    }else if(indexPath.row == 4){
        [self.navigationController pushViewController:[GeographyController new] animated:YES];
    }
}
@end
