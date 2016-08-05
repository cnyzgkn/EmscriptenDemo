//
//  VCSWrapper
//  emsVCS
//

#include "VCSAPI.h"
#include "VCSExt.h"
#include "stdio.h"
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

VCSMPoint3d getVCSMPoint3dAfterSolve(VCSMPoint3d* pt, VCSRigidBody* body)
{
    return pt->transformBy(body->transform());
}

VCSMLine3d getVCSMLine3dAfterSolve(VCSMLine3d* ln, VCSRigidBody* body)
{
    ln->transformBy(body->transform());
    return *ln;
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

//bind
EMSCRIPTEN_BINDINGS(VCSWrapper) {
    function("getVCSMPoint3dAfterSolve", &getVCSMPoint3dAfterSolve, allow_raw_pointers());
    function("getVCSMLine3dAfterSolve", &getVCSMLine3dAfterSolve, allow_raw_pointers());
    function("getVCSStatus", &getVCSStatus, allow_raw_pointers());

class_<VCSSystem>("VCSSystem")
    //.class_function("createVCSSystem", &VCSSystem::createVCSSystem, allow_raw_pointers())
    .constructor(&VCSSystem::createVCSSystem, allow_raw_pointers())
    /*.function("explosionFactor", &VCSSystem::explosionFactor)
    .function("conHandles", &VCSSystem::conHandles)
    .function("bodies", &VCSSystem::bodies)
    .function("solveMode", &VCSSystem::solveMode)
    .function("setExtCollDetector", &VCSSystem::setExtCollDetector, allow_raw_pointers())
    .function("attachBodyToReactor", &VCSSystem::attachBodyToReactor, allow_raw_pointers())
    .function("attachGroupToReactor", &VCSSystem::attachGroupToReactor, allow_raw_pointers())
    .function("removeBodyFromReactor", &VCSSystem::removeBodyFromReactor, allow_raw_pointers())
    .function("addExtVerificationCon", &VCSSystem::addExtVerificationCon, allow_raw_pointers())
    .function("isExtProfileRigid", &VCSSystem::isExtProfileRigid, allow_raw_pointers())
    .function("free", &VCSSystem::free)
    .function("clear", &VCSSystem::clear)
    .function("cre", &VCSSystem::cre)
    //.function("getBodiesFromConstraint", &VCSSystem::getBodiesFromConstraint, allow_raw_pointers())
    .function("getBodiesFromConstraint", select_overload<void(
        VCSConHandle*, 
        VCSRigidBody**, 
        VCSRigidBody**
        )>(&VCSSystem::getBodiesFromConstraint), allow_raw_pointers())
    .function("getConstraintInfo", &VCSSystem::getConstraintInfo, allow_raw_pointers())
    */
    //.function("solve", &VCSSystem::solve)
    .function("solve", select_overload<VCSStatus(
        VCSSolveMode,
        bool
        )>(&VCSSystem::solve), allow_raw_pointers())
    /*
    .function("drag", &VCSSystem::drag, allow_raw_pointers())
    .function("prioritizedDrag", &VCSSystem::prioritizedDrag)
    .function("preHybridDrag", &VCSSystem::preHybridDrag)
    .function("hybridDrag", &VCSSystem::hybridDrag)
    .function("postHybridDrag", &VCSSystem::postHybridDrag)
    .function("explode", &VCSSystem::explode)
    .function("numDOF", &VCSSystem::numDOF)
    .function("analyzeInconsistent", &VCSSystem::analyzeInconsistent, allow_raw_pointers())
    .function("oneBodyConstraintConflictAnalysis", &VCSSystem::oneBodyConstraintConflictAnalysis, allow_raw_pointers())
    .function("parametricSolve", &VCSSystem::parametricSolve, allow_raw_pointers())
    */
    //.function("createRBody", &VCSSystem::createRBody, allow_raw_pointers())
    .function("createRBody", select_overload<VCSStatus(
        VCSRigidBody**, 
        UINT_PTR,
        const VCSMMatrix3d&, 
        const VCSMPoint3d&
        )>(&VCSSystem::createRBody), allow_raw_pointers())
    .function("createRBody", select_overload<VCSRigidBody*(
        UINT_PTR,
        const VCSMMatrix3d&, 
        const VCSMPoint3d&
        )>(&VCSSystem::createRBody), allow_raw_pointers())
    .function("deleteRBody", &VCSSystem::deleteRBody, allow_raw_pointers())
    //.function("createGroup", &VCSSystem::createGroup, allow_raw_pointers())
    .function("createGroup", select_overload<VCSStatus(
        VCSGroupOfBodies**, 
        const VCSMMatrix3d&, 
        bool
        )>(&VCSSystem::createGroup), allow_raw_pointers())
    .function("getConstraintInfo", &VCSSystem::getConstraintInfo, allow_raw_pointers())
    .function("deleteGroup", &VCSSystem::deleteGroup, allow_raw_pointers())
    .function("deleteConstraint", &VCSSystem::deleteConstraint, allow_raw_pointers())
    /*
    .function("globalizeBodies", &VCSSystem::globalizeBodies)
    .function("localizeBodies", &VCSSystem::localizeBodies)
    .function("formRigidSet", &VCSSystem::formRigidSet)
    .function("flattern", &VCSSystem::flattern, allow_raw_pointers())
    .function("initialize", &VCSSystem::initialize)
    .function("solve1Body", &VCSSystem::solve1Body, allow_raw_pointers())
    .function("create3dDistPlPl", &VCSSystem::create3dDistPlPl, allow_raw_pointers())
    .function("create3dEqPlPl", &VCSSystem::create3dEqPlPl, allow_raw_pointers())
    .function("create3dEqPtPl", &VCSSystem::create3dEqPtPl, allow_raw_pointers())
    .function("create3dDistLnLn", &VCSSystem::create3dDistLnLn, allow_raw_pointers())
    .function("create3dSignedDistLnLn", &VCSSystem::create3dSignedDistLnLn, allow_raw_pointers())
    .function("create3dDistLnPl", &VCSSystem::create3dDistLnPl, allow_raw_pointers())
    .function("create3dDistPtPl", &VCSSystem::create3dDistPtPl, allow_raw_pointers())
    */
    //.function("create3dDistPtLn", &VCSSystem::create3dDistPtLn, allow_raw_pointers())
    .function("create3dDistPtLn", select_overload<VCSConHandle*(
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMPoint3d&, 
        const VCSMLine3d&, 
        VCSExtGeometry*,
        VCSExtGeometry*,
        double,
        VCSConEqMode,
        VCSVariable*
        )>(&VCSSystem::create3dDistPtLn), allow_raw_pointers())
    /*
    .function("create3dSignedDistPtLn", &VCSSystem::create3dSignedDistPtLn, allow_raw_pointers())
    */
    //.function("create3dDistPtPt", &VCSSystem::create3dDistPtPt, allow_raw_pointers())
    .function("create3dDistPtPt", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSExtGeometry*,
        VCSExtGeometry*,
        double,
        VCSConEqMode,
        VCSVariable*
        )>(&VCSSystem::create3dDistPtPt), allow_raw_pointers())
    .function("create3dDistPtPt", select_overload<VCSConHandle*(
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSExtGeometry*,
        VCSExtGeometry*,
        double,
        VCSConEqMode,
        VCSVariable*
        )>(&VCSSystem::create3dDistPtPt), allow_raw_pointers())
    /*
    .function("create3dSignedDistPtPt", &VCSSystem::create3dSignedDistPtPt, allow_raw_pointers())
    .function("create3dMateClCl", &VCSSystem::create3dMateClCl, allow_raw_pointers())
    .function("create3dMateSpSp", &VCSSystem::create3dMateSpSp, allow_raw_pointers())
    .function("create3dMateCnCn", &VCSSystem::create3dMateCnCn, allow_raw_pointers())
    .function("create3dMateSpCn", &VCSSystem::create3dMateSpCn, allow_raw_pointers())
    .function("create3dConCirCir", &VCSSystem::create3dConCirCir, allow_raw_pointers())
    .function("create3dAngVecVec", &VCSSystem::create3dAngVecVec, allow_raw_pointers())
    .function("create3dTanPlCl", &VCSSystem::create3dTanPlCl, allow_raw_pointers())
    .function("create3dTanClCl", &VCSSystem::create3dTanClCl, allow_raw_pointers())
    .function("create3dTanSpSp", &VCSSystem::create3dTanSpSp, allow_raw_pointers())
    .function("create3dTanPlCn", &VCSSystem::create3dTanPlCn, allow_raw_pointers())
    .function("create3dTanClCn", &VCSSystem::create3dTanClCn, allow_raw_pointers())
    .function("create3dTanClSp", &VCSSystem::create3dTanClSp, allow_raw_pointers())
    .function("create3dTanSpCn", &VCSSystem::create3dTanSpCn, allow_raw_pointers())
    .function("create3dTanCnCn", &VCSSystem::create3dTanCnCn, allow_raw_pointers())
    .function("create3dTanPlCir", &VCSSystem::create3dTanPlCir, allow_raw_pointers())
    .function("create3dTanCirCl", &VCSSystem::create3dTanCirCl, allow_raw_pointers())
    .function("create3dTanLnCl", &VCSSystem::create3dTanLnCl, allow_raw_pointers())
    .function("create3dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*, 
        VCSRigidBody*, 
        const VCSMCircle3d&, 
        const VCSMCircle3d&, 
        VCSExtGeometry*, 
        VCSExtGeometry*, 
        VCSVecSense, 
        double, 
        VCSConEqMode, 
        VCSRigidBody*, 
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirCir), allow_raw_pointers())
    .function("create3dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*, 
        const VCSMCircle3d&, 
        VCSVarGeomHandle*, 
        VCSExtGeometry*, 
        VCSExtGeometry*, 
        VCSVecSense, 
        double, 
        VCSConEqMode, 
        VCSRigidBody*, 
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirCir), allow_raw_pointers())
    .function("create3dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSVarGeomHandle*, 
        VCSVarGeomHandle*, 
        VCSExtGeometry*, 
        VCSExtGeometry*, 
        VCSVecSense,     
        double,    
        VCSConEqMode,     
        VCSRigidBody*,  
        const VCSMPoint3d& 
        )>(&VCSSystem::create3dTanCirCir), allow_raw_pointers())
    .function("create3dTanLnCir", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*, 
        const VCSMLine3d&, 
        const VCSMCircle3d&, 
        VCSExtGeometry*, 
        VCSExtGeometry*, 
        VCSVecSense,    
        double,    
        VCSConEqMode,     
        VCSRigidBody*,  
        const VCSMPoint3d& 
        )>(&VCSSystem::create3dTanLnCir), allow_raw_pointers())
    .function("create3dTanLnCir", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        const VCSMLine3d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*, 
        VCSExtGeometry*, 
        VCSVecSense,    
        double,    
        VCSConEqMode,     
        VCSRigidBody*,  
        const VCSMPoint3d& 
        )>(&VCSSystem::create3dTanLnCir), allow_raw_pointers())
    .function("create3dTanLnCur", &VCSSystem::create3dTanLnCur, allow_raw_pointers())
    .function("create3dTanCurCur", &VCSSystem::create3dTanCurCur, allow_raw_pointers())
    .function("create3dTanCirCur", select_overload<VCSStatus(
        VCSConHandle**, 
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*,
        const VCSMCircle3d&,
        VCSVecSense,        
        VCSExtCurve*,  
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dTanCirCur), allow_raw_pointers())
    .function("create3dTanCirCur", select_overload<VCSStatus(
        VCSConHandle**, 
        const VCSMPoint3d&, 
        VCSRigidBody*,
        VCSVarGeomHandle*,
        VCSVecSense,        
        VCSExtCurve*,  
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dTanCirCur), allow_raw_pointers())
    .function("create3dTanSurSur", &VCSSystem::create3dTanSurSur, allow_raw_pointers())
    .function("create3dTanPlSur", &VCSSystem::create3dTanPlSur, allow_raw_pointers())
    .function("create3dPerpCurSur", &VCSSystem::create3dPerpCurSur, allow_raw_pointers())
    .function("create3dMatePtCir", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*, 
        const VCSMPoint3d&, 
        const VCSMCircle3d&,
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dMatePtCir), allow_raw_pointers())
    .function("create3dMatePtCir", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        const VCSMPoint3d&, 
        VCSVarGeomHandle*, 
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dMatePtCir), allow_raw_pointers())
    .function("create3dMatePtEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*, 
        const VCSMPoint3d&, 
        const VCSMEllipse3d&,
        bool,
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dMatePtEll), allow_raw_pointers())
    .function("create3dMatePtEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*,  
        const VCSMPoint3d&, 
        VCSVarGeomHandle*,
        bool,
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dMatePtEll), allow_raw_pointers())
    .function("create3dTanLnEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*,
        const VCSMLine3d&, 
        const VCSMEllipse3d&, 
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create3dTanLnEll), allow_raw_pointers())
    .function("create3dTanLnEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        const VCSMLine3d&, 
        VCSVarGeomHandle*, 
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create3dTanLnEll), allow_raw_pointers())
    .function("create3dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*,
        const VCSMEllipse3d&, 
        const VCSMEllipse3d&, 
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dTanEllEll), allow_raw_pointers())
    .function("create3dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        const VCSMEllipse3d&, 
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dTanEllEll), allow_raw_pointers())
    .function("create3dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSVarGeomHandle*, 
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry* 
        )>(&VCSSystem::create3dTanEllEll), allow_raw_pointers())
    .function("create3dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        VCSRigidBody*, 
        const VCSMCircle3d&,
        const VCSMEllipse3d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirEll), allow_raw_pointers())
    .function("create3dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSRigidBody*, 
        const VCSMCircle3d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirEll), allow_raw_pointers())
    .function("create3dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSRigidBody*,
        const VCSMEllipse3d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirEll), allow_raw_pointers())
    .function("create3dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**, 
        bool,
        const VCSMPoint3d&, 
        const VCSMPoint3d&, 
        VCSVarGeomHandle*,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint3d&
        )>(&VCSSystem::create3dTanCirEll), allow_raw_pointers())
    .function("create3dMatePtCur", &VCSSystem::create3dMatePtCur, allow_raw_pointers())
    .function("create3dMatePtSur", &VCSSystem::create3dMatePtSur, allow_raw_pointers())
    .function("create3dGearCon", &VCSSystem::create3dGearCon, allow_raw_pointers())
    .function("create3dTransTan", &VCSSystem::create3dTransTan, allow_raw_pointers())
    .function("createPrWireWire", &VCSSystem::createPrWireWire, allow_raw_pointers())
    .function("create3dWeld", &VCSSystem::create3dWeld, allow_raw_pointers())
    .function("create3dSymmPtPtPl", &VCSSystem::create3dSymmPtPtPl, allow_raw_pointers())
    .function("create3dSymmVecVecPl", &VCSSystem::create3dSymmVecVecPl, allow_raw_pointers())
    .function("create3dSymmPlPlPl", &VCSSystem::create3dSymmPlPlPl, allow_raw_pointers())
    .function("create3dSymmLnLnPl", &VCSSystem::create3dSymmLnLnPl, allow_raw_pointers())
    .function("create3dSymmBodyBodyLn", &VCSSystem::create3dSymmBodyBodyLn, allow_raw_pointers())
    .function("create3dSymmPtPtLn", &VCSSystem::create3dSymmPtPtLn, allow_raw_pointers())
    .function("create3dSymmLnLnLn", &VCSSystem::create3dSymmLnLnLn, allow_raw_pointers())
    .function("create3dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMCircle3d&, 
        const VCSMCircle3d&, 
        VCSRigidBody*,
        const VCSMLine3d&
        )>(&VCSSystem::create3dSymmCirCirLn), allow_raw_pointers())
    .function("create3dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        const VCSMCircle3d&, 
        VCSRigidBody*,
        const VCSMLine3d&,
        VCSVarGeomHandle*
        )>(&VCSSystem::create3dSymmCirCirLn), allow_raw_pointers())
    .function("create3dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        const VCSMLine3d&, 
        VCSVarGeomHandle*,
        VCSVarGeomHandle*
        )>(&VCSSystem::create3dSymmCirCirLn), allow_raw_pointers())
    .function("create3dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMEllipse3d&, 
        const VCSMEllipse3d&, 
        VCSRigidBody*,
        const VCSMLine3d&
        )>(&VCSSystem::create3dSymmEllEllLn), allow_raw_pointers())
    .function("create3dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        const VCSMEllipse3d&, 
        VCSRigidBody*,
        const VCSMLine3d&,
        VCSVarGeomHandle*
        )>(&VCSSystem::create3dSymmEllEllLn), allow_raw_pointers())
    .function("create3dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**, 
        VCSRigidBody*,
        const VCSMLine3d&,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*
        )>(&VCSSystem::create3dSymmEllEllLn), allow_raw_pointers())
    .function("create3dOrderedPtsOnCur", &VCSSystem::create3dOrderedPtsOnCur, allow_raw_pointers())
    .function("create3dOrderedPtsOnLn", &VCSSystem::create3dOrderedPtsOnLn, allow_raw_pointers())
    .function("create3dPtsRectangularPattern", select_overload<VCSStatus(
        VCSPatternHandle**, 
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        VCSMPoint3d*,
        const VCSMVector3d&,
        const VCSMVector3d&,
        unsigned int,
        unsigned int,
        double,
        double, 
        bool
        )>(&VCSSystem::create3dPtsRectangularPattern), allow_raw_pointers())
    .function("create3dPtsRectangularPattern", select_overload<VCSStatus(
        VCSPatternHandle**, 
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        int*,
        VCSMPoint3d*,
        unsigned int,
        const VCSMVector3d&,
        const VCSMVector3d&,
        double,
        double, 
        bool
        )>(&VCSSystem::create3dPtsRectangularPattern), allow_raw_pointers())
    .function("create3dBodiesRectangularPattern", select_overload<VCSStatus(
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMVector3d&,
        const VCSMVector3d&,
        unsigned int,
        unsigned int,
        double,
        double, 
        bool
        )>(&VCSSystem::create3dBodiesRectangularPattern), allow_raw_pointers())
    .function("create3dBodiesRectangularPattern", select_overload<VCSStatus(
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        int*,
        unsigned int,
        const VCSMVector3d&,
        const VCSMVector3d&,
        double,
        double, 
        bool
        )>(&VCSSystem::create3dBodiesRectangularPattern), allow_raw_pointers())
    .function("create3dPtsCircularPattern", &VCSSystem::create3dPtsCircularPattern, allow_raw_pointers())
    .function("create3dVariableEllipse", &VCSSystem::create3dVariableEllipse, allow_raw_pointers())
    .function("create3dVariableCircle", &VCSSystem::create3dVariableCircle, allow_raw_pointers())
    .function("create3dVariableBSplineCurve", &VCSSystem::create3dVariableBSplineCurve, allow_raw_pointers())
    .function("create3dTranslationJoint", &VCSSystem::create3dTranslationJoint, allow_raw_pointers())
    .function("create3dRevoluteJoint", &VCSSystem::create3dRevoluteJoint, allow_raw_pointers())
    .function("create3dWeldJoint", &VCSSystem::create3dWeldJoint, allow_raw_pointers())
    .function("create3dBallJoint", &VCSSystem::create3dBallJoint, allow_raw_pointers())
    .function("create3dCylindricalJoint", &VCSSystem::create3dCylindricalJoint, allow_raw_pointers())
    .function("create3dPlanarJoint", &VCSSystem::create3dPlanarJoint, allow_raw_pointers())
    .function("create3dRevJoint", &VCSSystem::create3dRevJoint, allow_raw_pointers())
    .function("create3dTraJoint", &VCSSystem::create3dTraJoint, allow_raw_pointers())
    .function("create3dUJoint", &VCSSystem::create3dUJoint, allow_raw_pointers())
    .function("create3dOffsetCon", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint3d&,
        const VCSMPoint3d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMLine3d&,
        const VCSMLine3d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        double, 
        VCSConHandle*
        )>(&VCSSystem::create3dOffsetCon), allow_raw_pointers())
    .function("create3dOffsetCon", select_overload<VCSStatus(
        VCSConHandle**,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double, 
        VCSConHandle*
        )>(&VCSSystem::create3dOffsetCon), allow_raw_pointers())
    .function("create3dSignedDistCirCir", &VCSSystem::create3dSignedDistCirCir, allow_raw_pointers())
    .function("create3dMatePtPolyline", &VCSSystem::create3dMatePtPolyline, allow_raw_pointers())
    .function("create3dTanLnBSCur", &VCSSystem::create3dTanLnBSCur, allow_raw_pointers())
    .function("create3dTanCirBSCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint3d&,
        VCSRigidBody*,
        const VCSMCircle3d&,
        VCSVecSense,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create3dTanCirBSCur), allow_raw_pointers())
    .function("create3dTanCirBSCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint3d&,
        VCSVarGeomHandle*,
        VCSVecSense,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create3dTanCirBSCur), allow_raw_pointers())
    .function("create3dTanBSCurBSCur", &VCSSystem::create3dTanBSCurBSCur, allow_raw_pointers())
    .function("create2dVCSSystem", &VCSSystem::create2dVCSSystem, allow_raw_pointers())
    .function("create2dRBody", &VCSSystem::create2dRBody, allow_raw_pointers())
    .function("create3D2DGeometryMaping", &VCSSystem::create3D2DGeometryMaping, allow_raw_pointers())
    .function("create2dAngVecVec", &VCSSystem::create2dAngVecVec, allow_raw_pointers())
    .function("create2dMatePtCir", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMPoint2d&,
        const VCSMCircle2d&,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dMatePtCir), allow_raw_pointers())
    .function("create2dMatePtCir", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMPoint2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dMatePtCir), allow_raw_pointers())
    .function("create2dDistPtPt", &VCSSystem::create2dDistPtPt, allow_raw_pointers())
    .function("create2dDistPtLn", &VCSSystem::create2dDistPtLn, allow_raw_pointers())
    .function("create2dDistLnLn", &VCSSystem::create2dDistLnLn, allow_raw_pointers())
    .function("create2dGearCon", &VCSSystem::create2dGearCon, allow_raw_pointers())
    .function("create2dSymmBodyBodyLn", &VCSSystem::create2dSymmBodyBodyLn, allow_raw_pointers())
    .function("create2dSymmPtPtLn", &VCSSystem::create2dSymmPtPtLn, allow_raw_pointers())
    .function("create2dSymmLnLnLn", &VCSSystem::create2dSymmLnLnLn, allow_raw_pointers())
    .function("create2dSymmVecVecLn", &VCSSystem::create2dSymmVecVecLn, allow_raw_pointers())
    .function("create2dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMCircle2d&,
        const VCSMCircle2d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double,
        VCSConEqMode,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirCir), allow_raw_pointers())
    .function("create2dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        const VCSMCircle2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double,
        VCSConEqMode,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirCir), allow_raw_pointers())
    .function("create2dTanCirCir", select_overload<VCSStatus(
        VCSConHandle**,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double,
        VCSConEqMode,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirCir), allow_raw_pointers())
    .function("create2dTanLnCir", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMLine2d&,
        const VCSMCircle2d&, 
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double,
        VCSConEqMode,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanLnCir), allow_raw_pointers())
    .function("create2dTanLnCir", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSVecSense,
        double,
        VCSConEqMode,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanLnCir), allow_raw_pointers())
    .function("create2dMatePtEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMPoint2d&,
        const VCSMEllipse2d&,
        bool,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dMatePtEll), allow_raw_pointers())
    .function("create2dMatePtEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMPoint2d&,
        VCSVarGeomHandle*,
        bool,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dMatePtEll), allow_raw_pointers())
    .function("create2dTanLnEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMLine2d&,
        const VCSMEllipse2d&,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanLnEll), allow_raw_pointers())
    .function("create2dTanLnEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanLnEll), allow_raw_pointers())
    .function("create2dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMEllipse2d&,
        const VCSMEllipse2d&,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanEllEll), allow_raw_pointers())
    .function("create2dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMEllipse2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanEllEll), allow_raw_pointers())
    .function("create2dTanEllEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanEllEll), allow_raw_pointers())
    .function("create2dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMCircle2d&,
        const VCSMEllipse2d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirEll), allow_raw_pointers())
    .function("create2dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMCircle2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirEll), allow_raw_pointers())
    .function("create2dTanCirEll", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMEllipse2d&,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*,
        VCSRigidBody*,
        const VCSMPoint2d&
        )>(&VCSSystem::create2dTanCirEll), allow_raw_pointers())
    .function("create2dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMCircle2d&,
        const VCSMCircle2d&,
        VCSRigidBody*,
        const VCSMLine2d&
        )>(&VCSSystem::create2dSymmCirCirLn), allow_raw_pointers())
    .function("create2dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        const VCSMCircle2d&,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*
        )>(&VCSSystem::create2dSymmCirCirLn), allow_raw_pointers())
    .function("create2dSymmCirCirLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*
        )>(&VCSSystem::create2dSymmCirCirLn), allow_raw_pointers())
    .function("create2dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMEllipse2d&,
        const VCSMEllipse2d&,
        VCSRigidBody*,
        const VCSMLine2d&
        )>(&VCSSystem::create2dSymmEllEllLn), allow_raw_pointers())
    .function("create2dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        const VCSMEllipse2d&,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*
        )>(&VCSSystem::create2dSymmEllEllLn), allow_raw_pointers())
    .function("create2dSymmEllEllLn", select_overload<VCSStatus(
        VCSConHandle**,
        VCSRigidBody*,
        const VCSMLine2d&,
        VCSVarGeomHandle*,
        VCSVarGeomHandle*
        )>(&VCSSystem::create2dSymmEllEllLn), allow_raw_pointers())
    .function("create2dMatePtCur", &VCSSystem::create2dMatePtCur, allow_raw_pointers())
    .function("create2dTanLnCur", &VCSSystem::create2dTanLnCur, allow_raw_pointers())
    .function("create2dTanCurCur", &VCSSystem::create2dTanCurCur, allow_raw_pointers())
    .function("create2dTanCirCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMCircle2d&,
        VCSVecSense,
        VCSExtCurve2d*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanCirCur), allow_raw_pointers())
    .function("create2dTanCirCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSVarGeomHandle*,
        VCSVecSense,
        VCSExtCurve2d*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanCirCur), allow_raw_pointers())
    .function("create2dVariableEllipse", &VCSSystem::create2dVariableEllipse, allow_raw_pointers())
    .function("create2dVariableCircle", &VCSSystem::create2dVariableCircle, allow_raw_pointers())
    .function("create2dVariableBSplineCurve", &VCSSystem::create2dVariableBSplineCurve, allow_raw_pointers())
    .function("create2dSignedDistLnLn", &VCSSystem::create2dSignedDistLnLn, allow_raw_pointers())
    .function("create2dSignedDistPtLn", &VCSSystem::create2dSignedDistPtLn, allow_raw_pointers())
    .function("create2dSignedDistPtPt", &VCSSystem::create2dSignedDistPtPt, allow_raw_pointers())
    .function("create2dPtsRectangularPattern", select_overload<VCSStatus(
        VCSPatternHandle**,
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        VCSMPoint2d*,
        const VCSMVector2d&,
        const VCSMVector2d&,
        unsigned int,
        unsigned int,
        double,
        double,
        bool
        )>(&VCSSystem::create2dPtsRectangularPattern), allow_raw_pointers())
    .function("create2dPtsRectangularPattern", select_overload<VCSStatus(
        VCSPatternHandle**,
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        int*,
        VCSMPoint2d*,
        unsigned int,
        const VCSMVector2d&,
        const VCSMVector2d&,
        double,
        double,
        bool
        )>(&VCSSystem::create2dPtsRectangularPattern), allow_raw_pointers())
    .function("create2dBodiesRectangularPattern", select_overload<VCSStatus(
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMVector2d&,
        const VCSMVector2d&,
        unsigned int,
        unsigned int,
        double,
        double,
        bool
        )>(&VCSSystem::create2dBodiesRectangularPattern), allow_raw_pointers())
    .function("create2dBodiesRectangularPattern", select_overload<VCSStatus(
        VCSRigidBody**,
        VCSRigidBody*,
        VCSRigidBody*,
        int*,
        unsigned int,
        const VCSMVector2d&,
        const VCSMVector2d&,
        double,
        double,
        bool
        )>(&VCSSystem::create2dBodiesRectangularPattern), allow_raw_pointers())
    .function("create2dPtsCircularPattern", &VCSSystem::create2dPtsCircularPattern, allow_raw_pointers())
    .function("create2dBodiesCircularPattern", &VCSSystem::create2dBodiesCircularPattern, allow_raw_pointers())
    .function("create2dOffsetCon", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMLine2d&,
        const VCSMLine2d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        double,
        VCSConHandle*
        )>(&VCSSystem::create2dOffsetCon), allow_raw_pointers())
    .function("create2dOffsetCon", select_overload<VCSStatus(
        VCSConHandle**,
        bool,
        const VCSMPoint2d&,
        const VCSMPoint2d&,
        VCSRigidBody*,
        VCSRigidBody*,
        const VCSMLine2d&,
        const VCSMLine2d&,
        VCSExtGeometry*,
        VCSExtGeometry*,
        double,
        VCSConHandle*
        )>(&VCSSystem::create2dOffsetCon), allow_raw_pointers())
    .function("create2dSignedDistCirCir", &VCSSystem::create2dSignedDistCirCir, allow_raw_pointers())
    .function("create2dMatePtPolyline", &VCSSystem::create2dMatePtPolyline, allow_raw_pointers())
    .function("create2dEqualCirCir", &VCSSystem::create2dEqualCirCir, allow_raw_pointers())
    .function("create2dTanLnBSCur", &VCSSystem::create2dTanLnBSCur, allow_raw_pointers())
    .function("create2dTanCirBSCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint2d&,
        VCSRigidBody*,
        const VCSMCircle2d&,
        VCSVecSense,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanCirBSCur), allow_raw_pointers())
    .function("create2dTanCirBSCur", select_overload<VCSStatus(
        VCSConHandle**,
        const VCSMPoint2d&,
        VCSVarGeomHandle*,
        VCSVecSense,
        VCSVarGeomHandle*,
        VCSExtGeometry*,
        VCSExtGeometry*
        )>(&VCSSystem::create2dTanCirBSCur), allow_raw_pointers())
    .function("create2dTanBSCurBSCur", &VCSSystem::create2dTanBSCurBSCur, allow_raw_pointers())
    .function("conName", &VCSSystem::conName, allow_raw_pointers())
    .function("allContactRemoved", &VCSSystem::allContactRemoved)
    .function("outputResult", &VCSSystem::outputResult, allow_raw_pointers())
    .function("initializeLightSolve", &VCSSystem::initializeLightSolve)
    .function("lightSolve", &VCSSystem::lightSolve)
    .function("minMovementSolve", &VCSSystem::minMovementSolve)
    .function("bodyConstrainedStatusAnalysis", &VCSSystem::bodyConstrainedStatusAnalysis)
    .function("minMovementSolveForEqualCons", &VCSSystem::minMovementSolveForEqualCons, allow_raw_pointers())
    .function("tryMoveBody", &VCSSystem::tryMoveBody, allow_raw_pointers())
    .function("solveTimes", &VCSSystem::solveTimes)
    .function("incSolveTimes", &VCSSystem::incSolveTimes)
    .function("setInterruptTester", &VCSSystem::setInterruptTester)
    */
    ;

    class_<VCSMPoint3d>("VCSMPoint3d")
        .constructor<double, double, double>()
        .function("transformBy", &VCSMPoint3d::transformBy)
        .property("x", &VCSMPoint3d::x)
        .property("y", &VCSMPoint3d::y)
        .property("z", &VCSMPoint3d::z)
        ;

    class_<VCSMLine3d>("VCSMLine3d")
        .constructor<const VCSMPoint3d&, const VCSMPoint3d&>()
        .function("transformBy", &VCSMLine3d::transformBy)
        .property("mOrigin", &VCSMLine3d::pointOnLine, &VCSMLine3d::setPointOnLine)
        .property("mDirection", &VCSMLine3d::direction, &VCSMLine3d::setDirection)
        ;

    class_<VCSMVector3d>("VCSMVector3d")
        .constructor<double, double, double>()
        .function("transformBy", &VCSMVector3d::transformBy)
        .property("x", &VCSMVector3d::x)
        .property("y", &VCSMVector3d::y)
        .property("z", &VCSMVector3d::z)
        ;

    class_<VCSMMatrix3d>("VCSMMatrix3d")
        .constructor<>()
        ;

    class_<VCSRigidBody>("VCSRigidBody")
        .function("transform", &VCSRigidBody::transform)
        ;

    class_<VCSConHandle>("VCSConHandle")
        ;

    class_<VCSExtGeometry>("VCSExtGeometry")
        ;

    class_<VCSVariable>("VCSVariable")
        ;

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

    enum_<VCSConEqMode>("VCSConEqMode")
        .value("kVCSEQ", kVCSEQ)
        .value("kVCSLE", kVCSLE)
        .value("kVCSGE", kVCSGE)
        .value("kVCSMIN", kVCSMIN)
        ;

    enum_<VCSSolveMode>("VCSSolveMode")
        .value("kNormal", kNormal)
        .value("kFastNumeric", kFastNumeric)
        .value("kInternalOnly", kInternalOnly)
        .value("kForcedCompletion", kForcedCompletion)
        .value("kNoNumeric", kNoNumeric)
        .value("kNumericOnly", kNumericOnly)
        .value("kFlatten", kFlatten)
        .value("kDragging", kDragging)
        .value("kFastResolveInit", kFastResolveInit)
        .value("kDectectCollision", kDectectCollision)
        .value("kAnimateContact", kAnimateContact)
        .value("kDriving", kDriving)
        .value("kPrepositioning", kPrepositioning)
        .value("kNeedDOF", kNeedDOF)
        .value("kCollOption1", kCollOption1)
        .value("kCollOption2", kCollOption2)
        .value("kNoSetMerging", kNoSetMerging)
        .value("kNoReactorFiring", kNoReactorFiring)
        .value("kBodyOptimization", kBodyOptimization)
        .value("kLargeNumeric", kLargeNumeric)
        .value("k2D", k2D)
        .value("kJointAnalysis", kJointAnalysis)
        .value("kQuickPhaseII", kQuickPhaseII)
        ;

}


