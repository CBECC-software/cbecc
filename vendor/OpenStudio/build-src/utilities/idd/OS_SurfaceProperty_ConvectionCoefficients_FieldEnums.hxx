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

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_ConvectionCoefficientsFields
 *  \brief Enumeration of OS:SurfaceProperty:ConvectionCoefficients's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_ConvectionCoefficientsFields, )
#else
class OS_SurfaceProperty_ConvectionCoefficientsFields: public ::EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields> {
 public: 
  enum domain 
  {
Handle, SurfaceName, ConvectionCoefficient1Location, ConvectionCoefficient1Type, ConvectionCoefficient1, ConvectionCoefficient1ScheduleName, ConvectionCoefficient1UserCurveName, ConvectionCoefficient2Location, ConvectionCoefficient2Type, ConvectionCoefficient2, ConvectionCoefficient2ScheduleName, ConvectionCoefficient2UserCurveName,   };
  OS_SurfaceProperty_ConvectionCoefficientsFields()
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields>(Handle) {} 
  OS_SurfaceProperty_ConvectionCoefficientsFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields>(t_name) {} 
  OS_SurfaceProperty_ConvectionCoefficientsFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_ConvectionCoefficientsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields>::value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_ConvectionCoefficientsFields>;
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
{ OS_SurfaceProperty_ConvectionCoefficientsFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Location, "ConvectionCoefficient1Location", "Convection Coefficient 1 Location"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1Type, "ConvectionCoefficient1Type", "Convection Coefficient 1 Type"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1, "ConvectionCoefficient1", "Convection Coefficient 1"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1ScheduleName, "ConvectionCoefficient1ScheduleName", "Convection Coefficient 1 Schedule Name"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient1UserCurveName, "ConvectionCoefficient1UserCurveName", "Convection Coefficient 1 User Curve Name"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Location, "ConvectionCoefficient2Location", "Convection Coefficient 2 Location"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2Type, "ConvectionCoefficient2Type", "Convection Coefficient 2 Type"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2, "ConvectionCoefficient2", "Convection Coefficient 2"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2ScheduleName, "ConvectionCoefficient2ScheduleName", "Convection Coefficient 2 Schedule Name"},
{ OS_SurfaceProperty_ConvectionCoefficientsFields::ConvectionCoefficient2UserCurveName, "ConvectionCoefficient2UserCurveName", "Convection Coefficient 2 User Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_ConvectionCoefficientsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_ConvectionCoefficientsFields> OptionalOS_SurfaceProperty_ConvectionCoefficientsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_CONVECTIONCOEFFICIENTS_FIELDENUMS_HXX
