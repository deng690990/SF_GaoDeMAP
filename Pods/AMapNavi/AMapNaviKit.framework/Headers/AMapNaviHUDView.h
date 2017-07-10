//
//  AMapNaviHUDView.h
//  AMapNaviKit
//
//  Created by AutoNavi on 15/12/28.
//  Copyright © 2016年 AutoNavi. All rights reserved.
//

#import "AMapNaviCommonObj.h"
#import "AMapNaviDriveDataRepresentable.h"
#import "AMapNaviWalkDataRepresentable.h"

NS_ASSUME_NONNULL_BEGIN

@protocol AMapNaviHUDViewDelegate;

/**
 *  HUD导航界面
 *
 *  该类实现 AMapNaviDriveDataRepresentable 和 AMapNaviWalkDataRepresentable 协议,可以展示驾车HUD和步行HUD导航过程.
 */
@interface AMapNaviHUDView : UIView<AMapNaviDriveDataRepresentable, AMapNaviWalkDataRepresentable>

#pragma mark - Delegate

/**
 *  实现了 AMapNaviHUDViewDelegate 协议的类指针
 */
@property (nonatomic, weak) id<AMapNaviHUDViewDelegate> delegate;

#pragma mark - Options

/**
 *  是否采用横屏布局,默认NO
 */
@property (nonatomic, assign) BOOL isLandscape;

/**
 *  是否以镜像的方式显示,默认YES
 */
@property (nonatomic, assign) BOOL isMirror;

/**
 *  是否显示剩余距离,默认YES
 */
@property (nonatomic, assign) BOOL showRemainDistance;

/**
 *  是否显示剩余时间,默认YES
 */
@property (nonatomic, assign) BOOL showRemainTime;

@end

@protocol AMapNaviHUDViewDelegate <NSObject>

/**
 *  HUD导航界面返回按钮点击时的回调函数
 */
- (void)hudViewCloseButtonClicked:(AMapNaviHUDView *)hudView;

@end

NS_ASSUME_NONNULL_END
