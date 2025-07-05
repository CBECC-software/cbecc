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

#ifndef UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_DefrostCycleParametersFields
 *  \brief Enumeration of OS:Refrigeration:DefrostCycleParameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_DefrostCycleParametersFields, )
#else
class OS_Refrigeration_DefrostCycleParametersFields: public ::EnumBase<OS_Refrigeration_DefrostCycleParametersFields> {
 public: 
  enum domain 
  {
Handle, Name, DurationofDefrostCycle, DripDownTime, Defrost1HourStartTime, Defrost1MinuteStartTime, Defrost2HourStartTime, Defrost2MinuteStartTime, Defrost3HourStartTime, Defrost3MinuteStartTime, Defrost4HourStartTime, Defrost4MinuteStartTime, Defrost5HourStartTime, Defrost5MinuteStartTime, Defrost6HourStartTime, Defrost6MinuteStartTime, Defrost7HourStartTime, Defrost7MinuteStartTime, Defrost8HourStartTime, Defrost8MinuteStartTime,   };
  OS_Refrigeration_DefrostCycleParametersFields()
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(Handle) {} 
  OS_Refrigeration_DefrostCycleParametersFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(t_name) {} 
  OS_Refrigeration_DefrostCycleParametersFields(int t_value) 
   : EnumBase<OS_Refrigeration_DefrostCycleParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_DefrostCycleParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_DefrostCycleParametersFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_DefrostCycleParametersFields>;
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
{ OS_Refrigeration_DefrostCycleParametersFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_DefrostCycleParametersFields::Name, "Name", "Name"},
{ OS_Refrigeration_DefrostCycleParametersFields::DurationofDefrostCycle, "DurationofDefrostCycle", "Duration of Defrost Cycle"},
{ OS_Refrigeration_DefrostCycleParametersFields::DripDownTime, "DripDownTime", "Drip Down Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost1HourStartTime, "Defrost1HourStartTime", "Defrost 1 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost1MinuteStartTime, "Defrost1MinuteStartTime", "Defrost 1 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost2HourStartTime, "Defrost2HourStartTime", "Defrost 2 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost2MinuteStartTime, "Defrost2MinuteStartTime", "Defrost 2 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost3HourStartTime, "Defrost3HourStartTime", "Defrost 3 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost3MinuteStartTime, "Defrost3MinuteStartTime", "Defrost 3 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost4HourStartTime, "Defrost4HourStartTime", "Defrost 4 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost4MinuteStartTime, "Defrost4MinuteStartTime", "Defrost 4 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost5HourStartTime, "Defrost5HourStartTime", "Defrost 5 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost5MinuteStartTime, "Defrost5MinuteStartTime", "Defrost 5 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost6HourStartTime, "Defrost6HourStartTime", "Defrost 6 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost6MinuteStartTime, "Defrost6MinuteStartTime", "Defrost 6 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost7HourStartTime, "Defrost7HourStartTime", "Defrost 7 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost7MinuteStartTime, "Defrost7MinuteStartTime", "Defrost 7 Minute Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost8HourStartTime, "Defrost8HourStartTime", "Defrost 8 Hour Start Time"},
{ OS_Refrigeration_DefrostCycleParametersFields::Defrost8MinuteStartTime, "Defrost8MinuteStartTime", "Defrost 8 Minute Start Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_DefrostCycleParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_DefrostCycleParametersFields> OptionalOS_Refrigeration_DefrostCycleParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_DEFROSTCYCLEPARAMETERS_FIELDENUMS_HXX
