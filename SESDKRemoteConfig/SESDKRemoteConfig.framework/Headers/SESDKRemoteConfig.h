//
//  SESDKRemoteConfig.h
//  SESDKRemoteConfig
//
//  Created by Mobvista on 2022/11/30.
//

#import <Foundation/Foundation.h>
#import <SolarEngineSDK/SolarEngineSDK.h>
#import <objc/runtime.h>

#define SERCSDKVersion @"1.0.2.0"

typedef NS_ENUM(NSInteger, SERCMergeType) {
    SERCMergeTypeDefault      = 0, // 默认策略，读取缓存配置+默认配置跟服务端配置合并
    SERCMergeTypeUser         = 1, // App版本更新时，使用默认配置+服务端合并（丢弃缓存配置）
};

NS_ASSUME_NONNULL_BEGIN

/**
 
 初始化API示例
 #import <SolarEngineSDK/SolarEngineSDK.h>
 #import <SESDKRemoteConfig/SESDKRemoteConfig.h>
 
 SEConfig *config = [[SEConfig alloc] init];
 SERemoteConfig *remoteConfig = [[SERemoteConfig alloc] init];
 remoteConfig.enable = YES; // 开启在线参数功能
 config.remoteConfig = remoteConfig;
 [[SolarEngineSDK sharedInstance] startWithAppKey:your_appKey userId:your_userId_SolarEngine config:config];
 
 
 初始化后SDK会请求一次服务端配置，之后轮询每隔30分钟(默认情况)会再次请求服务端配置

 */
@interface SESDKRemoteConfig : NSObject


+ (SESDKRemoteConfig *)sharedInstance;

/**
 * 设置默认配置，当匹配不到服务端配置时会使用默认配置兜底
 *
 * @param defaultConfig 默认配置，一个参数配置为一个字典，格式如下：
  [
   {
         @"name" : @"k1", // 配置项的名称，对应fastFetchRemoteConfig接口的参数 key
         @"type" : @1, // 配置项的类型 1 string、2 integer、3 boolean、4 json
         @"value" : @"v1", // 配置项的值
   }
  ]
 */
- (void)setDefaultConfig:(NSArray *)defaultConfig;

/**
 * 设置自定义事件属性，请求参数配置时后端会使用该属性匹配
 *
 * @param properties 自定义事件属性，跟在后台页面设置的事件属性对应
 */
- (void)setRemoteConfigEventProperties:(NSDictionary *)properties;

/**
 * 设置自定义用户属性，请求参数配置时后端会使用该属性匹配
 *
 * @param properties 自定义用户属性, 跟在后台页面设置的用户属性对应
 */
- (void)setRemoteConfigUserProperties:(NSDictionary *)properties;

/**
 * 同步获取参数配置
 * 优先从缓存配置查询，查询不到则从默认配置查询，都查询不到则返回nil
 *
 * @param key  在后台页面设置的参数key，命中则返回对应值value
 */
- (id)fastFetchRemoteConfig:(NSString *)key;

/**
 * 异步获取参数配置
 * 请求服务端配置后与本地缓存配置合并，然后从缓存配置查询，查询不到则从默认配置中查询，都查询不到则返回nil
 *
 * @param key  在后台页面设置的参数key，命中则返回对应值value
 */
- (void)asyncFetchRemoteConfig:(NSString *)key
             completionHandler:(void (^)(id data))completionHandler;

/**
 *  设置debug模式，debug模式输出详细日志
 *
 * @param isDebug 是否是debug，默认为NO
 */
- (void)setDebug:(BOOL)isDebug;


@end





@interface SERemoteConfig : NSObject

/**
 线参数SDK启用开关，默认为关闭状态
*/
@property (nonatomic, assign) BOOL enable;

/**
自定义ID, 用来匹配用户在后台设置规则时设置的自定义ID
*/
@property (nonatomic, strong) NSDictionary *customIDProperties;

/**
 * 自定义ID 事件属性
 */
@property (nonatomic, strong) NSDictionary *customIDEventProperties;

/**
 * 自定义ID 用户属性
 */
@property (nonatomic, strong) NSDictionary *customIDUserProperties;


/**
SDK配置合并策略，默认情况下服务端配置跟本地缓存配置合并
ENUM：SERCMergeTypeUser 在App版本更新时会清除缓存配置
*/
@property (nonatomic, assign) SERCMergeType mergeType;

/**
请求后台配置轮询间隔，SDK初始化后默认每隔30分钟会请求一次服务端配置
pollInterval: 默认30分钟，支持设置的区间 30分钟 -- 24小时，单位：分钟
*/
@property (nonatomic, assign) int pollInterval;

/**
 *
 * 设置自定义 URL。需在 SDK 初始化之前调用
 */
@property(nonatomic, assign, nullable) NSString *customURL;

/// 是否开启 本地调试日志（不设置时默认不开启 本地日志）
@property (nonatomic, assign) BOOL logEnabled;


@end

@interface SEConfig (SERemoteConfig)

@property (nonatomic, strong) SERemoteConfig *remoteConfig;

@end


NS_ASSUME_NONNULL_END
