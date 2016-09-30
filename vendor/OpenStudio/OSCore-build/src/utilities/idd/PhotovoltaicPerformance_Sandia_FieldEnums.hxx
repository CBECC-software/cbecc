/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX
#define UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PhotovoltaicPerformance_SandiaFields
 *  \brief Enumeration of PhotovoltaicPerformance:Sandia's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PhotovoltaicPerformance_SandiaFields, )
#else
class PhotovoltaicPerformance_SandiaFields: public ::EnumBase<PhotovoltaicPerformance_SandiaFields> {
 public: 
  enum domain 
  {
Name, ActiveArea, NumberofCellsinSeries, NumberofCellsinParallel, ShortCircuitCurrent, OpenCircuitVoltage, CurrentatMaximumPowerPoint, VoltageatMaximumPowerPoint, SandiaDatabaseParameteraIsc, SandiaDatabaseParameteraImp, SandiaDatabaseParameterc0, SandiaDatabaseParameterc1, SandiaDatabaseParameterBVoc0, SandiaDatabaseParametermBVoc, SandiaDatabaseParameterBVmp0, SandiaDatabaseParametermBVmp, DiodeFactor, SandiaDatabaseParameterc2, SandiaDatabaseParameterc3, SandiaDatabaseParametera0, SandiaDatabaseParametera1, SandiaDatabaseParametera2, SandiaDatabaseParametera3, SandiaDatabaseParametera4, SandiaDatabaseParameterb0, SandiaDatabaseParameterb1, SandiaDatabaseParameterb2, SandiaDatabaseParameterb3, SandiaDatabaseParameterb4, SandiaDatabaseParameterb5, SandiaDatabaseParameterDelta_Tc_, SandiaDatabaseParameterfd, SandiaDatabaseParametera, SandiaDatabaseParameterb, SandiaDatabaseParameterc4, SandiaDatabaseParameterc5, SandiaDatabaseParameterIx0, SandiaDatabaseParameterIxx0, SandiaDatabaseParameterc6, SandiaDatabaseParameterc7,   };
  PhotovoltaicPerformance_SandiaFields()
   : EnumBase<PhotovoltaicPerformance_SandiaFields>(Name) {} 
  PhotovoltaicPerformance_SandiaFields(const std::string &t_name) 
   : EnumBase<PhotovoltaicPerformance_SandiaFields>(t_name) {} 
  PhotovoltaicPerformance_SandiaFields(int t_value) 
   : EnumBase<PhotovoltaicPerformance_SandiaFields>(t_value) {} 
  static std::string enumName() 
  { return "PhotovoltaicPerformance_SandiaFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PhotovoltaicPerformance_SandiaFields>::value()); }
   private:
    friend class EnumBase<PhotovoltaicPerformance_SandiaFields>;
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
{ PhotovoltaicPerformance_SandiaFields::Name, "Name", "Name"},
{ PhotovoltaicPerformance_SandiaFields::ActiveArea, "ActiveArea", "Active Area"},
{ PhotovoltaicPerformance_SandiaFields::NumberofCellsinSeries, "NumberofCellsinSeries", "Number of Cells in Series"},
{ PhotovoltaicPerformance_SandiaFields::NumberofCellsinParallel, "NumberofCellsinParallel", "Number of Cells in Parallel"},
{ PhotovoltaicPerformance_SandiaFields::ShortCircuitCurrent, "ShortCircuitCurrent", "Short Circuit Current"},
{ PhotovoltaicPerformance_SandiaFields::OpenCircuitVoltage, "OpenCircuitVoltage", "Open Circuit Voltage"},
{ PhotovoltaicPerformance_SandiaFields::CurrentatMaximumPowerPoint, "CurrentatMaximumPowerPoint", "Current at Maximum Power Point"},
{ PhotovoltaicPerformance_SandiaFields::VoltageatMaximumPowerPoint, "VoltageatMaximumPowerPoint", "Voltage at Maximum Power Point"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraIsc, "SandiaDatabaseParameteraIsc", "Sandia Database Parameter aIsc"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameteraImp, "SandiaDatabaseParameteraImp", "Sandia Database Parameter aImp"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc0, "SandiaDatabaseParameterc0", "Sandia Database Parameter c0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc1, "SandiaDatabaseParameterc1", "Sandia Database Parameter c1"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVoc0, "SandiaDatabaseParameterBVoc0", "Sandia Database Parameter BVoc0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVoc, "SandiaDatabaseParametermBVoc", "Sandia Database Parameter mBVoc"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterBVmp0, "SandiaDatabaseParameterBVmp0", "Sandia Database Parameter BVmp0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametermBVmp, "SandiaDatabaseParametermBVmp", "Sandia Database Parameter mBVmp"},
{ PhotovoltaicPerformance_SandiaFields::DiodeFactor, "DiodeFactor", "Diode Factor"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc2, "SandiaDatabaseParameterc2", "Sandia Database Parameter c2"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc3, "SandiaDatabaseParameterc3", "Sandia Database Parameter c3"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera0, "SandiaDatabaseParametera0", "Sandia Database Parameter a0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera1, "SandiaDatabaseParametera1", "Sandia Database Parameter a1"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera2, "SandiaDatabaseParametera2", "Sandia Database Parameter a2"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera3, "SandiaDatabaseParametera3", "Sandia Database Parameter a3"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera4, "SandiaDatabaseParametera4", "Sandia Database Parameter a4"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb0, "SandiaDatabaseParameterb0", "Sandia Database Parameter b0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb1, "SandiaDatabaseParameterb1", "Sandia Database Parameter b1"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb2, "SandiaDatabaseParameterb2", "Sandia Database Parameter b2"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb3, "SandiaDatabaseParameterb3", "Sandia Database Parameter b3"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb4, "SandiaDatabaseParameterb4", "Sandia Database Parameter b4"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb5, "SandiaDatabaseParameterb5", "Sandia Database Parameter b5"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterDelta_Tc_, "SandiaDatabaseParameterDelta_Tc_", "Sandia Database Parameter Delta(Tc)"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterfd, "SandiaDatabaseParameterfd", "Sandia Database Parameter fd"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParametera, "SandiaDatabaseParametera", "Sandia Database Parameter a"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterb, "SandiaDatabaseParameterb", "Sandia Database Parameter b"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc4, "SandiaDatabaseParameterc4", "Sandia Database Parameter c4"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc5, "SandiaDatabaseParameterc5", "Sandia Database Parameter c5"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIx0, "SandiaDatabaseParameterIx0", "Sandia Database Parameter Ix0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterIxx0, "SandiaDatabaseParameterIxx0", "Sandia Database Parameter Ixx0"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc6, "SandiaDatabaseParameterc6", "Sandia Database Parameter c6"},
{ PhotovoltaicPerformance_SandiaFields::SandiaDatabaseParameterc7, "SandiaDatabaseParameterc7", "Sandia Database Parameter c7"},
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
  inline std::ostream &operator<<(std::ostream &os, const PhotovoltaicPerformance_SandiaFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PhotovoltaicPerformance_SandiaFields> OptionalPhotovoltaicPerformance_SandiaFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_SANDIA_FIELDENUMS_HXX
