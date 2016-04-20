#include "UnormNormalize.h"

#if PLATFORM(IOS) && !USE(APPLE_INTERNAL_SDK)

#include <CoreFoundation/CFString.h>
#include <wtf/RetainPtr.h>

U_STABLE int32_t U_EXPORT2
ios_specific_unorm_normalize(const UChar *source, int32_t sourceLength,
                             UNormalizationMode mode, int32_t options,
                             UChar *resultBuffer, int32_t resultLength,
                             UErrorCode *status) {
    if (U_FAILURE(*status)) {
        return 0;
    }
    
    if ( (source == nullptr ? sourceLength != 0 : sourceLength < -1) ||
        (resultBuffer == nullptr ? resultLength != 0 : resultLength < 0) ||
        (source == resultBuffer && source != nullptr)
        ) {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }
    
    WTF::RetainPtr<CFMutableStringRef> normalizedString = WTF::adoptCF(CFStringCreateMutable(kCFAllocatorDefault, 0));
    CFStringAppendCharacters(normalizedString.get(), source, sourceLength);
    CFStringNormalizationForm normalizationForm;
    switch (mode) {
        case UNORM_NFC:
            normalizationForm = kCFStringNormalizationFormC;
            break;
        case UNORM_NFD:
            normalizationForm = kCFStringNormalizationFormD;
            break;
        case UNORM_NFKC:
            normalizationForm = kCFStringNormalizationFormKC;
            break;
        case UNORM_NFKD:
            normalizationForm = kCFStringNormalizationFormKD;
            break;
        default:
            RELEASE_ASSERT_NOT_REACHED();
            break;
    }
    
    CFStringNormalize(normalizedString.get(), normalizationForm);
    
    CFIndex normalizedLength = CFStringGetLength(normalizedString.get());
    if (normalizedLength > resultLength) {
        *status = U_BUFFER_OVERFLOW_ERROR;
    }
    
    if (resultLength > 0 && resultBuffer != nullptr) {
        CFStringGetCharacters(normalizedString.get(), CFRangeMake(0, resultLength), resultBuffer);
    }
    return normalizedLength;
}

#endif
