//
//  SpeechSynthesizer.h
//  AMapNaviKit
//
//  Created by 刘博 on 16/4/1.
//  Copyright © 2016年 AutoNavi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

/**
 *  iOS7及以上版本可以使用 AVSpeechSynthesizer 合成语音
 *
 *  或者采用"科大讯飞"等第三方的语音合成服务
 */
@interface SpeechSynthesizer : NSObject

+ (instancetype)sharedSpeechSynthesizer;

- (BOOL)isSpeaking;

- (void)speakString:(NSString *)string;

- (void)stopSpeak;

@end
