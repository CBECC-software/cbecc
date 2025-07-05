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

#ifndef UTILITIES_IDD_OS_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_QuadraticLinearFields
 *  \brief Enumeration of OS:Curve:QuadraticLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_QuadraticLinearFields, )
#else
class OS_Curve_QuadraticLinearFields: public ::EnumBase<OS_Curve_QuadraticLinearFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4y, Coefficient5x_TIMES_y, Coefficient6x_POW_2_TIMES_y, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, InputUnitTypeforY, OutputUnitType,   };
  OS_Curve_QuadraticLinearFields()
   : EnumBase<OS_Curve_QuadraticLinearFields>(Handle) {} 
  OS_Curve_QuadraticLinearFields(const std::string &t_name) 
   : EnumBase<OS_Curve_QuadraticLinearFields>(t_name) {} 
  OS_Curve_QuadraticLinearFields(int t_value) 
   : EnumBase<OS_Curve_QuadraticLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_QuadraticLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_QuadraticLinearFields>::value()); }
   private:
    friend class EnumBase<OS_Curve_QuadraticLinearFields>;
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
{ OS_Curve_QuadraticLinearFields::Handle, "Handle", "Handle"},
{ OS_Curve_QuadraticLinearFields::Name, "Name", "Name"},
{ OS_Curve_QuadraticLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ OS_Curve_QuadraticLinearFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ OS_Curve_QuadraticLinearFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ OS_Curve_QuadraticLinearFields::Coefficient4y, "Coefficient4y", "Coefficient4 y"},
{ OS_Curve_QuadraticLinearFields::Coefficient5x_TIMES_y, "Coefficient5x_TIMES_y", "Coefficient5 x*y"},
{ OS_Curve_QuadraticLinearFields::Coefficient6x_POW_2_TIMES_y, "Coefficient6x_POW_2_TIMES_y", "Coefficient6 x**2*y"},
{ OS_Curve_QuadraticLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_QuadraticLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_QuadraticLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ OS_Curve_QuadraticLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ OS_Curve_QuadraticLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_QuadraticLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_QuadraticLinearFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ OS_Curve_QuadraticLinearFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ OS_Curve_QuadraticLinearFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_QuadraticLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_QuadraticLinearFields> OptionalOS_Curve_QuadraticLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_QUADRATICLINEAR_FIELDENUMS_HXX
