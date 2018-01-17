using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MestraApp
{
    /// <summary>
    /// Removes whitespace at start/end, comments and empty lines.
    /// </summary>
    public class CommentRemover
    {
        private readonly ConfigFileContent _content;

        public CommentRemover(ConfigFileContent content)
        {
            _content = content;
        }

        public void Run()
        {
            var newLines = new List<string>();
            // Strip lines.
            foreach (var line in _content.Lines)
            {
                var adaptedLine = line;

                // Find // and remove.
                var indexComment = line.IndexOf("//", StringComparison.Ordinal);
                if (indexComment >= 0)
                {
                    adaptedLine = line.Substring(0, indexComment);
                }

                adaptedLine = adaptedLine.Trim();

                if (!string.IsNullOrEmpty(adaptedLine))
                {
                    newLines.Add(adaptedLine);
                }
            }

            _content.Lines = newLines;
        }
    }
}
