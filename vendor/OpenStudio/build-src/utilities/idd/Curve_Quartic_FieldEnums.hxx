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

#ifndef UTILITIES_IDD_CURVE_QUARTIC_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_QUARTIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_QuarticFields
 *  \brief Enumeration of Curve:Quartic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_QuarticFields, )
#else
class Curve_QuarticFields: public ::EnumBase<Curve_QuarticFields> {
 public: 
  enum domain 
  {
Name, Coefficient1Constant, Coefficient2x, Coefficient3x_POW_2, Coefficient4x_POW_3, Coefficient5x_POW_4, MinimumValueofx, MaximumValueofx, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforX, OutputUnitType,   };
  Curve_QuarticFields()
   : EnumBase<Curve_QuarticFields>(Name) {} 
  Curve_QuarticFields(const std::string &t_name) 
   : EnumBase<Curve_QuarticFields>(t_name) {} 
  Curve_QuarticFields(int t_value) 
   : EnumBase<Curve_QuarticFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_QuarticFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_QuarticFields>::value()); }
   private:
    friend class EnumBase<Curve_QuarticFields>;
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
{ Curve_QuarticFields::Name, "Name", "Name"},
{ Curve_QuarticFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ Curve_QuarticFields::Coefficient2x, "Coefficient2x", "Coefficient2 x"},
{ Curve_QuarticFields::Coefficient3x_POW_2, "Coefficient3x_POW_2", "Coefficient3 x**2"},
{ Curve_QuarticFields::Coefficient4x_POW_3, "Coefficient4x_POW_3", "Coefficient4 x**3"},
{ Curve_QuarticFields::Coefficient5x_POW_4, "Coefficient5x_POW_4", "Coefficient5 x**4"},
{ Curve_QuarticFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_QuarticFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_QuarticFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_QuarticFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_QuarticFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Curve_QuarticFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_QuarticFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_QuarticFields> OptionalCurve_QuarticFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_QUARTIC_FIELDENUMS_HXX
