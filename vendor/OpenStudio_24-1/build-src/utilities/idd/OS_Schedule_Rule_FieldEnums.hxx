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

#ifndef UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_RuleFields
 *  \brief Enumeration of OS:Schedule:Rule's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_RuleFields, )
#else
class OS_Schedule_RuleFields: public ::EnumBase<OS_Schedule_RuleFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleRulesetName, RuleOrder, DayScheduleName, ApplySunday, ApplyMonday, ApplyTuesday, ApplyWednesday, ApplyThursday, ApplyFriday, ApplySaturday, DateSpecificationType, StartMonth, StartDay, EndMonth, EndDay,   };
  OS_Schedule_RuleFields()
   : EnumBase<OS_Schedule_RuleFields>(Handle) {} 
  OS_Schedule_RuleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_RuleFields>(t_name) {} 
  OS_Schedule_RuleFields(int t_value) 
   : EnumBase<OS_Schedule_RuleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_RuleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_RuleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_RuleFields>;
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
{ OS_Schedule_RuleFields::Handle, "Handle", "Handle"},
{ OS_Schedule_RuleFields::Name, "Name", "Name"},
{ OS_Schedule_RuleFields::ScheduleRulesetName, "ScheduleRulesetName", "Schedule Ruleset Name"},
{ OS_Schedule_RuleFields::RuleOrder, "RuleOrder", "Rule Order"},
{ OS_Schedule_RuleFields::DayScheduleName, "DayScheduleName", "Day Schedule Name"},
{ OS_Schedule_RuleFields::ApplySunday, "ApplySunday", "Apply Sunday"},
{ OS_Schedule_RuleFields::ApplyMonday, "ApplyMonday", "Apply Monday"},
{ OS_Schedule_RuleFields::ApplyTuesday, "ApplyTuesday", "Apply Tuesday"},
{ OS_Schedule_RuleFields::ApplyWednesday, "ApplyWednesday", "Apply Wednesday"},
{ OS_Schedule_RuleFields::ApplyThursday, "ApplyThursday", "Apply Thursday"},
{ OS_Schedule_RuleFields::ApplyFriday, "ApplyFriday", "Apply Friday"},
{ OS_Schedule_RuleFields::ApplySaturday, "ApplySaturday", "Apply Saturday"},
{ OS_Schedule_RuleFields::DateSpecificationType, "DateSpecificationType", "Date Specification Type"},
{ OS_Schedule_RuleFields::StartMonth, "StartMonth", "Start Month"},
{ OS_Schedule_RuleFields::StartDay, "StartDay", "Start Day"},
{ OS_Schedule_RuleFields::EndMonth, "EndMonth", "End Month"},
{ OS_Schedule_RuleFields::EndDay, "EndDay", "End Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_RuleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_RuleFields> OptionalOS_Schedule_RuleFields ;
#endif

/** \class OS_Schedule_RuleExtensibleFields
 *  \brief Enumeration of OS:Schedule:Rule's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_RuleExtensibleFields, )
#else
class OS_Schedule_RuleExtensibleFields: public ::EnumBase<OS_Schedule_RuleExtensibleFields> {
 public: 
  enum domain 
  {
SpecificMonth, SpecificDay,   };
  OS_Schedule_RuleExtensibleFields()
   : EnumBase<OS_Schedule_RuleExtensibleFields>(SpecificMonth) {} 
  OS_Schedule_RuleExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_RuleExtensibleFields>(t_name) {} 
  OS_Schedule_RuleExtensibleFields(int t_value) 
   : EnumBase<OS_Schedule_RuleExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_RuleExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_RuleExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_RuleExtensibleFields>;
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
{ OS_Schedule_RuleExtensibleFields::SpecificMonth, "SpecificMonth", "Specific Month"},
{ OS_Schedule_RuleExtensibleFields::SpecificDay, "SpecificDay", "Specific Day"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_RuleExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_RuleExtensibleFields> OptionalOS_Schedule_RuleExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_RULE_FIELDENUMS_HXX
