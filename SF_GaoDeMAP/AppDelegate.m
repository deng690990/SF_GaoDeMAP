//
//  AppDelegate.m
//  SF_GaoDeMAP
//
//  Created by 首牛 on 2017/6/6.
//  Copyright © 2017年 ShouNew.com. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //设置APIKEY
    [AMapServices sharedServices].apiKey = APIKEY;
    [AMapServices sharedServices].enableHTTPS = YES;
    return YES;
}




@end
