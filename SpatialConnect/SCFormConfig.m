/**
 * Copyright 2016 Boundless http://boundlessgeo.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */

#import "SCFormConfig.h"
#import "SCFormConfig.h"

@implementation SCFormConfig

@synthesize identifier, fields, name;

- (id)initWithDict:(NSDictionary *)dict {
  self = [super init];
  if (self) {
    self.name = dict[@"name"];
    self.identifier = [dict[@"id"] integerValue];
    self.fields = dict[@"fields"];
  }
  return self;
}

- (NSInteger)strToFormType:(NSString *)s {
  if ([s containsString:@"string"]) {
    return SCFORM_TYPE_STRING;
  } else if ([s containsString:@"number"]) {
    return SCFORM_TYPE_NUMBER;
  } else if ([s containsString:@"boolean"]) {
    return SCFORM_TYPE_BOOLEAN;
  } else if ([s containsString:@"integer"]) {
    return SCFORM_TYPE_INTEGER;
  } else if ([s containsString:@"date"]){
    return SCFORM_TYPE_DATE;
  } else if ([s containsString:@"slider"]) {
    return SCFORM_TYPE_SLIDER;
  } else if ([s containsString:@"counter"]) {
    return SCFORM_TYPE_COUNTER;
  } else if ([s containsString:@"select"]) {
    return SCFORM_TYPE_SELECT;
  }
  return -1;
}

- (NSString *)formTypeToStr:(NSNumber *)n {
  SCFormItemType t = [n integerValue];
  if (t == SCFORM_TYPE_STRING) {
    return @"string";
  } else if (t == SCFORM_TYPE_NUMBER) {
    return @"number";
  } else if (t == SCFORM_TYPE_BOOLEAN) {
    return @"boolean";
  } else if (t == SCFORM_TYPE_INTEGER) {
    return @"integer";
  } else if (t == SCFORM_TYPE_DATE) {
    return @"date";
  } else if (t == SCFORM_TYPE_SLIDER) {
    return @"slider";
  } else if (t == SCFORM_TYPE_COUNTER) {
    return @"counter";
  } else if (t == SCFORM_TYPE_SELECT) {
    return @"select";
  }
  return nil;
}

- (NSString *)formTypeToSQLType:(SCFormItemType)t {
  if (t == SCFORM_TYPE_STRING) {
    return @"TEXT";
  } else if (t == SCFORM_TYPE_NUMBER) {
    return @"REAL";
  } else if (t == SCFORM_TYPE_BOOLEAN) {
    return @"INTEGER";
  } else if (t == SCFORM_TYPE_INTEGER) {
    return @"INTEGER";
  } else if (t == SCFORM_TYPE_DATE) {
    return @"DATETIME";
  } else if (t == SCFORM_TYPE_SLIDER) {
    return @"REAL";
  } else if (t == SCFORM_TYPE_COUNTER) {
    return @"INTEGER";
  } else if (t == SCFORM_TYPE_SELECT) {
    return @"TEXT";
  }
  return @"NULL";
}

- (NSString *)stringToSQLType:(NSString *)t {
  if ([t isEqualToString:@"string"]) {
    return @"TEXT";
  } else if ([t isEqualToString:@"number"]) {
    return @"REAL";
  } else if ([t isEqualToString:@"boolean"]) {
    return @"INTEGER";
  } else if ([t isEqualToString:@"date"]) {
    return @"DATETIME";
  } else if ([t isEqualToString:@"slider"]) {
    return @"REAL";
  } else if ([t isEqualToString:@"counter"]) {
    return @"INTEGER";
  } else if ([t isEqualToString:@"select"]) {
    return @"TEXT";
  }
  return @"NULL";
}

- (NSDictionary *)sqlTypes {
  NSMutableDictionary *t = [NSMutableDictionary new];
  [self.fields enumerateObjectsUsingBlock:^(NSDictionary *d, NSUInteger idx,
                                            BOOL *stop) {
    NSString *key = [NSString stringWithString:d[@"key"]];
    NSString *type = d[@"type"];
    [t setValue:[self stringToSQLType:type] forKey:key];
  }];
  return [NSDictionary dictionaryWithDictionary:t];
}

- (NSString*)name {
  return [[name lowercaseString] stringByReplacingOccurrencesOfString:@" " withString:@"_"];
}

- (NSDictionary*)JSONDict {
  NSMutableDictionary *dict = [NSMutableDictionary new];
  dict[@"layer_name"] = self.name;
  dict[@"display_name"] = name;
  dict[@"id"] = @(self.identifier);
  dict[@"fields"] = self.fields;
  return [NSDictionary dictionaryWithDictionary:dict];
}

@end