/*****************************************************************************
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
******************************************************************************/

#import "SCAuthService.h"
#import "SCBackendService.h"
#import "SCCache.h"
#import "SCConfigService.h"
#import "SCDataService.h"
#import "SCFileUtils.h"
#import "SCGeoJSON.h"
#import "SCJavascriptCommands.h"
#import "SCLineString.h"
#import "SCRCTBridge.h"
#import "SCRasterStore.h"
#import "SCSensorService.h"
#import "SCService.h"
#import "SCSimplePoint.h"
#import "SCSpatialStore.h"
#import "SCSpatialStore.h"
#import "SCStoreStatusEvent.h"
#import "WebViewJavascriptBridge.h"
#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

@interface SpatialConnect : NSObject {
  NSMutableArray *filepaths;
}

@property(readonly, strong) SCDataService *dataService;
@property(readonly, strong) SCSensorService *sensorService;
@property(readonly, strong) SCConfigService *configService;
@property(readonly, strong) SCAuthService *authService;
@property(readonly, strong) SCBackendService *backendService;
@property(readonly, strong) SCCache *cache;

@property(readonly) RACMulticastConnection *serviceEvents;

/**
 This singleton of SpatialConnect is shared across your app.

 @return instance of SpatialConnect
 */
+ (id)sharedInstance;

/**
 @discussion This starts all the services in the order they were added. Data,
 Sensor, Config, and Auth are all started. Backend Service waits for the Config
 service to find a remote backend.

 @brief starts all the services
 */
- (void)startAllServices;

/**
 @discussion Stops all the services in the order they were added to the services
 dictionary.

 @brief stops the services
 */
- (void)stopAllServices;

/**
 @description Stops all the services and then restarts them in the order they
 are added to the dictionary.

 @brief restarts the services
 */
- (void)restartAllServices;

/**
 @description Adds an instantiated instance of Service that extends the
 SCService class. The 'service' must extend the SCService class.

 @brief adds a service to the SpatialConnect instance

 @param service instance of SCService class
 */
- (void)addService:(SCService *)service;

/**
 @description this stops and removes a service from the SpatialConnect instance.

 @brief removes a service from the SpatialConnect instance

 @param serviceId Service's unique identifier
 */
- (void)removeService:(NSString *)serviceId;

/**
 @discussion This is the preferred way to fetch a service from the spatial
 connect instance.

 @param ident a service's unique id

 @return the instance of the service
 */
- (SCService *)serviceById:(NSString *)ident;

/**
 @discussion This is the preferred way to start a service.

 @warning do not call service start on the service instance. Use this method to
 start a service.

 @brief starts a single service

 @param serviceId the unique id of the service.
 */
- (void)startService:(NSString *)serviceId;

/**
 @discussion This is the preferred way to stop a service.

 @warning do not call service stop on the service instance. Use this method to
 stop a service.

 @brief stops a single service

 @param serviceId the unique id of the service.
 */
- (void)stopService:(NSString *)serviceId;

/**
 @discussion This is the preferred way to restart a service.

 @warning do not call service restart on the service instance. Use this method
 to start a service.

 @brief restarts a single service

 @param serviceId the unique id of the service.
 */
- (void)restartService:(NSString *)serviceId;

/**
 @discussion If you have an instance of SpatialConnect Server, this is how you
 would register it. Passing in a remote configuration object will use the info
 to start the connection to the backend.

 @brief connects to SpatialConnect Server

 @param r remote configuration
 */
- (void)connectBackend:(SCRemoteConfig *)r;

/**
 @discussion this is the unique identifier that is App Store compliant and used
 to uniquely identify the installation id which is unique per install on a
 device. ID's tied to the hardware are not allowed to be used by the app store

 @brief unique identifier

 @return UUID string of the install id.
 */
- (NSString *)deviceIdentifier;

/**
 @description emits an SCServiceStatusEvent when the service is running. If the
 service isn't started, this will wait until it is started. This can be by your
 app to start wiring up functionality waiting for it to occur. This is the best
 way to know if a service is started. If the service is already started, it will
 return an event immediately. You can also receive errors in the subscribe's
 error block. The observable will complete when the store is confirmed to have
 started.

 @brief An observable to listen for store start

 @param serviceId a services unique id

 @return RACSignal that emits when the service is running
 */
- (RACSignal *)serviceRunning:(NSString *)serviceId;

@end
