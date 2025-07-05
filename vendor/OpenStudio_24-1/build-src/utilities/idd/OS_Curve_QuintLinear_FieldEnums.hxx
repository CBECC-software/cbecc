/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_OS_CURVE_QUINTLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_QUINTLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_QuintLinearFields
 *  \brief Enumeration of OS:Curve:QuintLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_QuintLinearFields, )
#else
class OS_Curve_QuintLinearFields: public ::EnumBase<OS_Curve_QuintLinearFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1Constant, Coefficient2v, Coefficient3w, Coefficient4x, Coefficient5y, Coefficient6z, MinimumValueofv, MaximumValueofv, MinimumValueofw, MaximumValueofw, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumValueofz, MaximumValueofz, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforv, InputUnitTypeforw, InputUnitTypeforx, InputUnitTypefory, InputUnitTypeforz,   };
  OS_Curve_QuintLinearFields()
   : EnumBase<OS_Curve_QuintLinearFields>(Handle) {} 
  OS_Curve_QuintLinearFields(const std::string &t_name) 
   : EnumBase<OS_Curve_QuintLinearFields>(t_name) {} 
  OS_Curve_QuintLinearFields(int t_value) 
   : EnumBase<OS_Curve_QuintLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_QuintLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_QuintLinearFields>::value()); }
   private:
    friend class EnumBase<OS_Curve_QuintLinearFields>;
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
{ OS_Curve_QuintLinearFields::Handle, "Handle", "Handle"},
{ OS_Curve_QuintLinearFields::Name, "Name", "Name"},
{ OS_Curve_QuintLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ OS_Curve_QuintLinearFields::Coefficient2v, "Coefficient2v", "Coefficient2 v"},
{ OS_Curve_QuintLinearFields::Coefficient3w, "Coefficient3w", "Coefficient3 w"},
{ OS_Curve_QuintLinearFields::Coefficient4x, "Coefficient4x", "Coefficient4 x"},
{ OS_Curve_QuintLinearFields::Coefficient5y, "Coefficient5y", "Coefficient5 y"},
{ OS_Curve_QuintLinearFields::Coefficient6z, "Coefficient6z", "Coefficient6 z"},
{ OS_Curve_QuintLinearFields::MinimumValueofv, "MinimumValueofv", "Minimum Value of v"},
{ OS_Curve_QuintLinearFields::MaximumValueofv, "MaximumValueofv", "Maximum Value of v"},
{ OS_Curve_QuintLinearFields::MinimumValueofw, "MinimumValueofw", "Minimum Value of w"},
{ OS_Curve_QuintLinearFields::MaximumValueofw, "MaximumValueofw", "Maximum Value of w"},
{ OS_Curve_QuintLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_QuintLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_QuintLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ OS_Curve_QuintLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ OS_Curve_QuintLinearFields::MinimumValueofz, "MinimumValueofz", "Minimum Value of z"},
{ OS_Curve_QuintLinearFields::MaximumValueofz, "MaximumValueofz", "Maximum Value of z"},
{ OS_Curve_QuintLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_QuintLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_QuintLinearFields::InputUnitTypeforv, "InputUnitTypeforv", "Input Unit Type for v"},
{ OS_Curve_QuintLinearFields::InputUnitTypeforw, "InputUnitTypeforw", "Input Unit Type for w"},
{ OS_Curve_QuintLinearFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ OS_Curve_QuintLinearFields::InputUnitTypefory, "InputUnitTypefory", "Input Unit Type for y"},
{ OS_Curve_QuintLinearFields::InputUnitTypeforz, "InputUnitTypeforz", "Input Unit Type for z"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_QuintLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_QuintLinearFields> OptionalOS_Curve_QuintLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_QUINTLINEAR_FIELDENUMS_HXX
