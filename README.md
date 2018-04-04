# SF_GaoDeMAP
> 先来点前言：本人在开发项目过程中，遇到各种高德的神操作，通过学习官方sdk文档，结合demo，进行了二次封装，要实现这几个功能只需几句代码。写下这篇博客，希望大家给予佐证，共同进步。

废话不多说，直奔主题。

### 一、准备工作
我们要做高德地图相关的应用，首先得注册一个高德账号（一般以公司名义注册，如果是个人项目，就注册个人账号）。进入[高德开放平台注册](http://lbs.amap.com/dev/id/newuser)。当然有高德账号的同仁请忽略这一步。当你注册并登陆成功后我们就可以正式进入高德开发之旅了。

#### 1、进入控制台
![QQ20170708-101558.png](http://upload-images.jianshu.io/upload_images/5351221-cca8bfa3a3686232.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2、创建应用

![QQ20170708-102327.png](http://upload-images.jianshu.io/upload_images/5351221-5d3c4bedfb7e7c7b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![QQ20170708-102643.png](http://upload-images.jianshu.io/upload_images/5351221-050d2a748f6e8b9d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 3、添加key
		
![QQ20170708-102824.png](http://upload-images.jianshu.io/upload_images/5351221-475fceedc600273c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![QQ20170708-103058.png](http://upload-images.jianshu.io/upload_images/5351221-27287683e1b7ae34.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### Bundle ID
![QQ20170708-103222.png](http://upload-images.jianshu.io/upload_images/5351221-05cfe78070822ba0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 4、利用pod导入高德的相关sdk
```objective-c
//相信pod大家都用过，我就不具体介绍如何安装和使用cocoaPods了
pod 'AFNetworking'
pod 'AMap3DMap', '~>4.4.1'
pod 'AMapSearch' #搜索服务SDK
pod 'AMapLocation'
pod 'AMapNavi'#这个要放到其他高德sdk后
pod 'JZLocationConverter'#gps纠偏
```

>假如不懂cocoapods使用的，看这篇文章[http://blog.csdn.net/e62ces0iem/article/details/73550884](http://blog.csdn.net/e62ces0iem/article/details/73550884)

#### 5、将高德生成的key放到APPdelegate.h文件中

![QQ20170708-104047.png](http://upload-images.jianshu.io/upload_images/5351221-4275552b36c2cdcb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```objective-c
//基础定位类
#import <AMapFoundationKit/AMapFoundationKit.h>
//高德地图基础类
#import <MAMapKit/MAMapKit.h>
//定义一个宏来保存高德的apikey
#define APIKEY @"a80ff3043934c4cb4a3af35b6b20b32"
```

#### 6、在APPdelegate.m文件里设置相关内容
```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //设置APIKEY
    [AMapServices sharedServices].apiKey = APIKEY;
    [AMapServices sharedServices].enableHTTPS = YES;
    return YES;
}
```

#### 7、在plist文件中开启定位服务

![QQ20171219-180121.png](http://upload-images.jianshu.io/upload_images/5351221-1f0e4e13c5d2866a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 二、实现地图相关功能

#### 1、将我封装好的包导入项目中

![QQ20170708-135921.png](http://upload-images.jianshu.io/upload_images/5351221-ad1923cf5eef225d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2、导入头文件
```objective-c
#import "MapManager.h"
```

#### 3、只显示地图和小蓝点
```objective-c
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
```

#### 4、给指定坐标添加一个大头针
```objective-c

- (void)viewDidLoad {
	[super viewDidLoad];
	//不管进行什么地图操作都要先定位自己位置
	[self locationOnlySelf];
	CLLocationCoordinate2D coor;
	coor.latitude = 30.566666;//
	coor.longitude = 104.054536;
	[[MapManager sharedManager] addAnomationWithCoor:coor];
}
```

#### 5、搜索附近并大头针标记（能实时导航，带语音）
```objective-c
- (void)viewDidLoad {
    [super viewDidLoad];
    //不管进行什么地图操作都要先定位自己位置
    [self locationOnlySelf];
    [self searchAround];
}
//附近搜索
-(void)searchAround{
    //可以设置大头针图片，没有设置图片就用默认图片
//    [MapManager sharedManager].destinationImgName = @"首牛";
//    [MapManager sharedManager].locationPointImgName = @"首牛";
    [[MapManager sharedManager] searchAroundWithKeyWords:@"景点"];//关键词可以随便写，只要高德能搜索的
}
```

#### 6、假如要做历史轨迹连线，最好新建一个VC
```objective-c
- (void)viewDidLoad {
    [super viewDidLoad];
    MapManager *manager = [MapManager sharedManager];
    manager.controller = self;
    [manager initMapView];
    [manager.mapView setZoomLevel:13.1 animated:YES];
    //存放历史轨迹点坐标的数组
    NSArray *array = @[@"39.822136,116.35095",@"39.832136,116.42095",@"39.902136,116.42095",@"39.902136,116.44095"];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [manager drawLineWithArray:array];
        [manager addAnomationWithArray:array];
    });
    
}
```

### 三、来谈谈纠偏功能的实现和语音播报功能的实现

#### 1、GPS纠偏一般用于硬件获取的GPS转为高德的GPS，因为相同地方每种地图的GPS是不相同的，所以需要用到这个三方JZLocationConverter[GitHub下载地址](https://github.com/JackZhouCn/JZLocationConverter)，作者有详细的使用指南。

#### 2、语音播报功能

##### （1）首先把我这个包拖到你的工程里

![QQ20170708-143020.png](http://upload-images.jianshu.io/upload_images/5351221-11bf5d81cdc15944.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### （2）代码实现
```objective-c
//重写高德导航自带的一个回调方法中开启语音
- (BOOL)driveManagerIsNaviSoundPlaying:(AMapNaviDriveManager *)driveManager
{
    return [[SpeechSynthesizer sharedSpeechSynthesizer] isSpeaking];
}
//关闭导航的回调方法中关掉语音
-(void)driveViewCloseButtonClicked:(AMapNaviDriveView *)driveView{
    [self.driveManager stopNavi];
    [driveView removeFromSuperview];
    //停止语音
    [[SpeechSynthesizer sharedSpeechSynthesizer] stopSpeak];
}

```

### 四、demo下载地址及效果图


![高德demo.gif](http://upload-images.jianshu.io/upload_images/5351221-c921713cb07b05f7.gif?imageMogr2/auto-orient/strip)


### 最后，运行该demo最好是在真机上，更能体现效果。注意假如你是用模拟器运行该demo，一定要确保你的模拟器已经设置了经纬度。
>#### 先点一下模拟器任意位置，然后如图操作：
![
![Uploading 设置经纬度_332955.png . . .]](http://upload-images.jianshu.io/upload_images/5351221-148774ba43cf1ea2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


![QQ20170912-155709.png](http://upload-images.jianshu.io/upload_images/5351221-dab6a73e70757359.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
