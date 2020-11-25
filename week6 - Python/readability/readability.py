import cs50

"""
Some assumptions on text input:
- It is trimmed: no leading or trailing whitespace.
- Word and sentence boundaries are single characters, not multiple runs.
  (i.e., there are no empty words "  " or sentences "..")
- Proper syntax: space between sentences and ends with a sentence terminator.
"""


def is_letter(c):
    return c.isalpha()


def is_sentence(c):
    """Actually `is_sentence_terminator()`"""
    return c in ('.?!')


def is_word(c):
    """Actually `is_word_terminator()`"""
    return (c == ' ')


def coleman_liau(l, w, s):
    """Rounding is performed by caller, so the "raw" index is available if needed"""
    L = 100.0 * l / w
    S = 100.0 * s / w
    return 0.0588 * L - 0.296 * S - 15.8


def main():
    text = cs50.get_string("Text: ")
    letters = words = sentences = 0

    for c in text:
        if is_letter(c):
            letters += 1

        elif is_word(c):
            words += 1

        # Intentionally disregards sentence terminators as word terminators.
        # Since it is assumed there is a space between all sentences,
        # the last the word of the previous sentence will be accounted for.
        elif is_sentence(c):
            sentences += 1

    # Account for the last word on last sentence (i.e., the last word on text)
    words += 1

    idx = round(coleman_liau(letters, words, sentences))

    if (idx < 1):
        print("Before Grade 1")

    elif (idx >= 16):
        print("Grade 16+")

    else:
        print(f"Grade {idx}")


if __name__ == "__main__":
    main()
