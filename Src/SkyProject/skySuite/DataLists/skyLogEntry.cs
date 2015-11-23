using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace skySuite.DataLists
{
    public enum skyLogType
    {
        FATAL_ERROR = 0,
	    CRITICAL_ERROR = 1,
	    ASSERT_ERROR = 2,
	    WARNING = 3,
	    INFO = 4,
	    MEMORY_ALLOCATION = 5,
	    MEMORY_DELETION = 6
    }

    public class skyLogEntry
    {
        public skyLogType Type { get; set; }
        public DateTime Time { get; set; }
        public string Function { get; set; }
        public string Message { get; set; }
        public string File { get; set; }

        public skyLogEntry(skyLogType a_eType, DateTime a_cTime, string a_strFunction, string a_strMessage, string a_strFile)
        {
            Type = a_eType;
            Time = a_cTime;
            Function = a_strFunction;
            Message = a_strMessage;
            File = a_strFile;
        }
    }
}
