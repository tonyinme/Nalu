/*------------------------------------------------------------------------*/
/*  Copyright 2014 National Renewable Energy Laboratory.                  */
/*  This software is released under the license detailed                  */
/*  in the file, LICENSE, which is located in the top-level Nalu          */
/*  directory structure                                                   */
/*------------------------------------------------------------------------*/

#ifndef TurbKineticEnergyKsgsSrcElemKernel_H
#define TurbKineticEnergyKsgsSrcElemKernel_H

#include "Kernel.h"
#include "FieldTypeDef.h"

#include <stk_mesh/base/BulkData.hpp>
#include <stk_mesh/base/Entity.hpp>

#include <Kokkos_Core.hpp>

namespace sierra {
namespace nalu {

class SolutionOptions;
class MasterElement;
class ElemDataRequests;

/** Add Ksgs source term for kernel-based algorithm approach
 */
template<typename AlgTraits>
class TurbKineticEnergyKsgsSrcElemKernel: public Kernel
{
public:
  TurbKineticEnergyKsgsSrcElemKernel(
    const stk::mesh::BulkData&,
    const SolutionOptions&,
    ElemDataRequests&);

  virtual ~TurbKineticEnergyKsgsSrcElemKernel();

  /** Execute the kernel within a Kokkos loop and populate the LHS and RHS for
   *  the linear solve
   */
  virtual void execute(
    SharedMemView<DoubleType**>&,
    SharedMemView<DoubleType*>&,
    ScratchViews<DoubleType>&);

private:
  TurbKineticEnergyKsgsSrcElemKernel() = delete;

  ScalarFieldType *tkeNp1_{nullptr};
  ScalarFieldType *densityNp1_{nullptr};
  ScalarFieldType *tvisc_{nullptr};
  ScalarFieldType *dualNodalVolume_{nullptr};
  GenericFieldType *Gju_{nullptr};

  double cEps_{0.0};
  double tkeProdLimitRatio_{0.0};
  
  /// Integration point to node mapping
  const int* ipNodeMap_;
};

}  // nalu
}  // sierra

#endif /* TurbKineticEnergyKsgsSrcElemKernel_H */
