#include <emscripten.h>
#include <emscripten/bind.h>


using namespace emscripten;

enum VCSStatus {

    // general
    //
    kNull,
    kError,
    kFailed,
    kBadMatrix,
    kOK,
    kExternallySolved,       // not currently returned
    kPartiallySolved,        // not currently returned
    kFatallyInconsistent,    // not currently returned
    kExternallyInterrupted,

    // solve and constraint status
    //
    kSolved,
    kSolvedMakingAssumptions,
    kInconsistent,
    kSolvedWithoutDOFAndRedundancyAnalysis,
    kSolvedWithExternalVerificationFailure,
    kRedundant,
    kJointDOFLocked,

    // constraint only status
    //
    kNotSolved,
    kRotationSolvedOnly,
    kTranslationSolvedOnly,
    kRotationRedundantOnly,
    kTranslationRedundantOnly,
    kSolvedButRotationRedundant,
    kSolvedButTranslationRedundant,
};

VCSStatus solve()
{
    return kSolved;
} 

std::string getVCSStatus(VCSStatus status)
{
        // general
             if(status == kNull) return "kNull";
        else if(status == kError) return "kError";
        else if(status == kFailed) return "kFailed";
        else if(status == kBadMatrix) return "kBadMatrix";
        else if(status == kOK) return "kOK";
        else if(status == kExternallySolved) return "kExternallySolved";
        else if(status == kPartiallySolved) return "kPartiallySolved";
        else if(status == kFatallyInconsistent) return "kFatallyInconsistent";
        else if(status == kExternallyInterrupted) return "kExternallyInterrupted";

        // solve and constraint status
        else if(status == kSolved) return "kSolved";
        else if(status == kSolvedMakingAssumptions) return "kSolvedMakingAssumptions";
        else if(status == kInconsistent) return "kInconsistent";
        else if(status == kSolvedWithoutDOFAndRedundancyAnalysis) return "kSolvedWithoutDOFAndRedundancyAnalysis";
        else if(status == kSolvedWithExternalVerificationFailure) return "kSolvedWithExternalVerificationFailure";
        else if(status == kRedundant) return "kRedundant";
        else if(status == kJointDOFLocked) return "kJointDOFLocked";

        // constraint only status
        else if(status == kNotSolved) return "kNotSolved";
        else if(status == kRotationSolvedOnly) return "kRotationSolvedOnly";
        else if(status == kTranslationSolvedOnly) return "kTranslationSolvedOnly";
        else if(status == kRotationRedundantOnly) return "kRotationRedundantOnly";
        else if(status == kTranslationRedundantOnly) return "kTranslationRedundantOnly";
        else if(status == kSolvedButRotationRedundant) return "kSolvedButRotationRedundant";
        else if(status == kSolvedButTranslationRedundant) return "kSolvedButTranslationRedundant";
}

EMSCRIPTEN_BINDINGS(VCSWrapper) {
    function("solve", &solve);
    function("getVCSStatus", &getVCSStatus);

    enum_<VCSStatus>("VCSStatus")
        // general
        .value("kNull", kNull)
        .value("kError", kError)
        .value("kFailed", kFailed)
        .value("kBadMatrix", kBadMatrix)
        .value("kOK", kOK)
        .value("kExternallySolved", kExternallySolved)
        .value("kPartiallySolved", kPartiallySolved)
        .value("kFatallyInconsistent", kFatallyInconsistent)
        .value("kExternallyInterrupted", kExternallyInterrupted)
        // solve and constraint status
        .value("kSolved", kSolved)
        .value("kSolvedMakingAssumptions", kSolvedMakingAssumptions)
        .value("kInconsistent", kInconsistent)
        .value("kSolvedWithoutDOFAndRedundancyAnalysis", kSolvedWithoutDOFAndRedundancyAnalysis)
        .value("kSolvedWithExternalVerificationFailure", kSolvedWithExternalVerificationFailure)
        .value("kRedundant", kRedundant)
        .value("kJointDOFLocked", kJointDOFLocked)
        // constraint only status
        .value("kNotSolved", kNotSolved)
        .value("kRotationSolvedOnly", kRotationSolvedOnly)
        .value("kTranslationSolvedOnly", kTranslationSolvedOnly)
        .value("kRotationRedundantOnly", kRotationRedundantOnly)
        .value("kTranslationRedundantOnly", kTranslationRedundantOnly)
        .value("kSolvedButRotationRedundant", kSolvedButRotationRedundant)
        .value("kSolvedButTranslationRedundant", kSolvedButTranslationRedundant)
        ;
}

