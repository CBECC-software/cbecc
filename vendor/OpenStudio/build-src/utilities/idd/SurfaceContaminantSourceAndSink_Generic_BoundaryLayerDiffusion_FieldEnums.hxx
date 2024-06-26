/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SURFACECONTAMINANTSOURCEANDSINK_GENERIC_BOUNDARYLAYERDIFFUSION_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACECONTAMINANTSOURCEANDSINK_GENERIC_BOUNDARYLAYERDIFFUSION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields
 *  \brief Enumeration of SurfaceContaminantSourceAndSink:Generic:BoundaryLayerDiffusion's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields, )
#else
class SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields: public ::EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields> {
 public: 
  enum domain 
  {
Name, SurfaceName, MassTransferCoefficient, ScheduleName, HenryAdsorptionConstantorPartitionCoefficient,   };
  SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields()
   : EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields>(Name) {} 
  SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields(const std::string &t_name) 
   : EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields>(t_name) {} 
  SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields(int t_value) 
   : EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields>::value()); }
   private:
    friend class EnumBase<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::Name, "Name", "Name"},
{ SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::MassTransferCoefficient, "MassTransferCoefficient", "Mass Transfer Coefficient"},
{ SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields::HenryAdsorptionConstantorPartitionCoefficient, "HenryAdsorptionConstantorPartitionCoefficient", "Henry Adsorption Constant or Partition Coefficient"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields> OptionalSurfaceContaminantSourceAndSink_Generic_BoundaryLayerDiffusionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACECONTAMINANTSOURCEANDSINK_GENERIC_BOUNDARYLAYERDIFFUSION_FIELDENUMS_HXX
