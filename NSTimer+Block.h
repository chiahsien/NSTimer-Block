//
//  NSTimer+Block.h
//
//  Created by Nelson on 2017/3/31.
//

#import <Foundation/Foundation.h>

@interface NSTimer (Block)

/**
 * Creates and returns a new NSTimer object and schedules it on the current run loop in the default mode.
 * After `interval` seconds have elapsed, the timer fires, executing `block`.
 *
 * @param interval The number of seconds between firings of the timer.
 *                 If `interval` is less than or equal to `0.0`, this method chooses the nonnegative value
 *                 of `0.1` milliseconds instead.
 * @param repeats If `YES`, the timer will repeatedly reschedule itself until invalidated.
 *                If `NO`, the timer will be invalidated after it fires.
 * @param block A block to be executed when the timer fires.
 *              The timer itself is passed as the parameter to this block when executed to aid in avoiding
 *              cyclical references.
 * @return A new NSTimer object, configured according to the specified parameters.
 */
+ (NSTimer *)cht_scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

/**
 * Creates and returns a new NSTimer object initialized with the specified block object.
 * After `interval` seconds have elapsed, the timer fires, executing `block`.
 * @note You must add the new timer to a run loop, using `addTimer:forMode:`.
 *       (If the timer is configured to repeat, there is no need to subsequently re-add the timer to the run loop.)
 *
 * @param interval The number of seconds between firings of the timer.
 *                 If `interval` is less than or equal to `0.0`, this method chooses the nonnegative value
 *                 of `0.1` milliseconds instead.
 * @param repeats If `YES`, the timer will repeatedly reschedule itself until invalidated.
 *                If `NO`, the timer will be invalidated after it fires.
 * @param block A block to be executed when the timer fires.
 *              The timer itself is passed as the parameter to this block when executed to aid in avoiding
 *              cyclical references.
 * @return A new NSTimer object, configured according to the specified parameters.
 */
+ (NSTimer *)cht_timerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

@end
