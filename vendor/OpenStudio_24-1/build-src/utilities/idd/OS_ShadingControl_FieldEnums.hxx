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

#ifndef UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ShadingControlFields
 *  \brief Enumeration of OS:ShadingControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ShadingControlFields, )
#else
class OS_ShadingControlFields: public ::EnumBase<OS_ShadingControlFields> {
 public: 
  enum domain 
  {
Handle, Name, ShadingType, ConstructionwithShadingName, ShadingDeviceMaterialName, ShadingControlType, ScheduleName, Setpoint, ShadingControlIsScheduled, GlareControlIsActive, TypeofSlatAngleControlforBlinds, SlatAngleScheduleName, Setpoint2, MultipleSurfaceControlType,   };
  OS_ShadingControlFields()
   : EnumBase<OS_ShadingControlFields>(Handle) {} 
  OS_ShadingControlFields(const std::string &t_name) 
   : EnumBase<OS_ShadingControlFields>(t_name) {} 
  OS_ShadingControlFields(int t_value) 
   : EnumBase<OS_ShadingControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingControlFields>::value()); }
   private:
    friend class EnumBase<OS_ShadingControlFields>;
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
{ OS_ShadingControlFields::Handle, "Handle", "Handle"},
{ OS_ShadingControlFields::Name, "Name", "Name"},
{ OS_ShadingControlFields::ShadingType, "ShadingType", "Shading Type"},
{ OS_ShadingControlFields::ConstructionwithShadingName, "ConstructionwithShadingName", "Construction with Shading Name"},
{ OS_ShadingControlFields::ShadingDeviceMaterialName, "ShadingDeviceMaterialName", "Shading Device Material Name"},
{ OS_ShadingControlFields::ShadingControlType, "ShadingControlType", "Shading Control Type"},
{ OS_ShadingControlFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ShadingControlFields::Setpoint, "Setpoint", "Setpoint"},
{ OS_ShadingControlFields::ShadingControlIsScheduled, "ShadingControlIsScheduled", "Shading Control Is Scheduled"},
{ OS_ShadingControlFields::GlareControlIsActive, "GlareControlIsActive", "Glare Control Is Active"},
{ OS_ShadingControlFields::TypeofSlatAngleControlforBlinds, "TypeofSlatAngleControlforBlinds", "Type of Slat Angle Control for Blinds"},
{ OS_ShadingControlFields::SlatAngleScheduleName, "SlatAngleScheduleName", "Slat Angle Schedule Name"},
{ OS_ShadingControlFields::Setpoint2, "Setpoint2", "Setpoint 2"},
{ OS_ShadingControlFields::MultipleSurfaceControlType, "MultipleSurfaceControlType", "Multiple Surface Control Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingControlFields> OptionalOS_ShadingControlFields ;
#endif

/** \class OS_ShadingControlExtensibleFields
 *  \brief Enumeration of OS:ShadingControl's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ShadingControlExtensibleFields, )
#else
class OS_ShadingControlExtensibleFields: public ::EnumBase<OS_ShadingControlExtensibleFields> {
 public: 
  enum domain 
  {
SubSurfaceName,   };
  OS_ShadingControlExtensibleFields()
   : EnumBase<OS_ShadingControlExtensibleFields>(SubSurfaceName) {} 
  OS_ShadingControlExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ShadingControlExtensibleFields>(t_name) {} 
  OS_ShadingControlExtensibleFields(int t_value) 
   : EnumBase<OS_ShadingControlExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ShadingControlExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ShadingControlExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ShadingControlExtensibleFields>;
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
{ OS_ShadingControlExtensibleFields::SubSurfaceName, "SubSurfaceName", "Sub Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ShadingControlExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ShadingControlExtensibleFields> OptionalOS_ShadingControlExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SHADINGCONTROL_FIELDENUMS_HXX
