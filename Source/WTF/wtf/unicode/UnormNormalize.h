//
//  UnormNormalize.h
//  WTF

#ifndef UnormNormalize_h
#define UnormNormalize_h

#include <wtf/ExportMacros.h>
#include <unicode/unorm.h>

#if PLATFORM(IOS) && !USE(APPLE_INTERNAL_SDK)

U_STABLE int32_t U_EXPORT2
ios_specific_unorm_normalize(const UChar *source, int32_t sourceLength,
                             UNormalizationMode mode, int32_t options,
                             UChar *result, int32_t resultLength,
                             UErrorCode *status);

#endif

#endif /* UnormNormalize_h */
