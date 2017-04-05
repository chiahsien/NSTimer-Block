//
//  NSTimer+Block.m
//
//  Created by Nelson on 2017/3/31.
//

#import "NSTimer+Block.h"

@implementation NSTimer (Block)

#pragma mark - Public methods

+ (NSTimer *)cht_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block {
    NSTimer *t = [self scheduledTimerWithTimeInterval:interval
                                               target:self
                                             selector:@selector(cht_invokeBlock:)
                                             userInfo:[block copy]
                                              repeats:repeats];
    return t;
}

+ (NSTimer *)cht_timerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block {
    NSTimer *t = [self timerWithTimeInterval:interval
                                      target:self
                                    selector:@selector(cht_invokeBlock:)
                                    userInfo:[block copy]
                                     repeats:repeats];
    return t;
}

#pragma mark - Private methods

+ (void)cht_invokeBlock:(NSTimer *)timer {
    void (^block)(NSTimer *) = timer.userInfo;
    if (block) {
        block(timer);
    }
}

@end
