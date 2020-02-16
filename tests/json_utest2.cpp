#include <iostream>

#include "./../json.hpp"
#include "./utest.hpp"
#include "./make_json.hpp"


class test33 {
public:
    std::string to_string() const {
        return "123";
    }
};

class test44 {
public:
    std::string to_string(amo::memory_buffer<std::string> buffer) const {
        return "123";
    }
};
class test55 {
public:
    template<typename T>
    std::string to_string(amo::memory_buffer<T>& buffer) const {
        return "123";
    }
};


TEST(json_file, pass) {
    json_type json2 = amo::string_reader({ R"( {
        "zero": 0,
        "one": 1,
        "space": " ",
        "quote": "\"",
        "backslash": "\\",
        "controls": "\b\f\n\r\t"1})" });
    EXPECT_EQ(json2.is_valid(), false);
    
    for (int i = 1; i <= 3; ++i) {
        char path[FILENAME_MAX] = { 0 };
        sprintf(path, "./data/jsonchecker/pass%02d.json", i);
        
        json_type json(amo::file_reader{ path });
        
        if (!json.is_valid()) {
            std::cout << "parse file: " << path << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), true);
    }
}

TEST(json_file, fail) {
    for (int i = 1; i <= 34; ++i) {
        char path[FILENAME_MAX] = { 0 };
        sprintf(path, "./data/jsonchecker/fail%02d.json", i);
        
        json_type json(amo::file_reader{ path });
        
        if (json.is_valid()) {
            std::cout << "parse file: " << path << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), false);
    }
}

TEST(json_file, roundtrip) {
    for (int i = 1; i <= 27; ++i) {
        char path[FILENAME_MAX] = { 0 };
        sprintf(path, "./data/roundtrip/roundtrip%02d.json", i);
        
        json_type json(amo::file_reader{ path });
        
        if (!json.is_valid()) {
            std::cout << "parse file: " << path << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), true);
    }
}

TEST(json_file, data_txt) {
    std::ifstream ifs("./data/data.txt");
    
    while (ifs.is_open() && !ifs.eof()) {
        char buffer[1024] = { 0 };
        ifs.getline(buffer, 1024);
        
        if (ifs.gcount() <= 0) {
            continue;
        }
        
        std::string filename = "./data/" ;
        filename += buffer;
        json_type json = amo::file_reader{ filename };
        
        if (!json.is_valid()) {
            std::cout << "parse file: " << filename << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), true);
    }
    
}

TEST(json_file, error2) {

    std::vector<std::string> error_json_files = {
        "data/nst_json_testsuite/test_parsing/i_number_neg_int_huge_exp.json",
        "data/nst_json_testsuite/test_parsing/i_number_pos_double_huge_exp.json",
        //"data/nst_json_testsuite/test_parsing/i_object_key_lone_2nd_surrogate.json",  // key里面不支持处理特殊字符
        "data/nst_json_testsuite/test_parsing/i_string_1st_surrogate_but_2nd_missing.json",
        "data/nst_json_testsuite/test_parsing/i_string_1st_valid_surrogate_2nd_invalid.json",
        "data/nst_json_testsuite/test_parsing/i_string_incomplete_surrogates_escape_valid.json",
        "data/nst_json_testsuite/test_parsing/i_string_incomplete_surrogate_and_escape_valid.json",
        "data/nst_json_testsuite/test_parsing/i_string_incomplete_surrogate_pair.json",
        "data/nst_json_testsuite/test_parsing/i_string_inverted_surrogates_U+1D11E.json",
        "data/nst_json_testsuite/test_parsing/i_string_lone_second_surrogate.json",
        //"data/nst_json_testsuite/test_parsing/i_string_not_in_unicode_range.json",      // unicode 暂未解决
        //"data/nst_json_testsuite/test_parsing/i_string_truncated-utf-8.json",           // unicode
        //"data/nst_json_testsuite/test_parsing/i_string_unicode_U+10FFFE_nonchar.json",  //unicode
        //"data/nst_json_testsuite/test_parsing/i_string_unicode_U+1FFFE_nonchar.json",  //unicode
        //"data/nst_json_testsuite/test_parsing/i_string_unicode_U+FDD0_nonchar.json",       // unicode
        //"data/nst_json_testsuite/test_parsing/i_string_unicode_U+FFFE_nonchar.json",      // unicode
        "data/nst_json_testsuite/test_parsing/i_string_UTF-16_invalid_lonely_surrogate.json",
        "data/nst_json_testsuite/test_parsing/i_string_UTF-16_invalid_surrogate.json",
        //"data/nst_json_testsuite/test_parsing/i_string_UTF-8_invalid_sequence.json", //   unicode
        //"data/nst_json_testsuite/test_parsing/i_structure_500_nested_arrays.json", // 递归500次基本上没问题
        "data/nst_json_testsuite/test_parsing/i_structure_UTF-8_BOM_empty_object.json",
        "data/nst_json_testsuite/test_parsing/n_array_1_true_without_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_a_invalid_utf8.json",
        "data/nst_json_testsuite/test_parsing/n_array_colon_instead_of_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_comma_after_close.json",
        "data/nst_json_testsuite/test_parsing/n_array_comma_and_number.json",
        "data/nst_json_testsuite/test_parsing/n_array_double_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_double_extra_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_extra_close.json",
        "data/nst_json_testsuite/test_parsing/n_array_extra_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_incomplete.json",
        "data/nst_json_testsuite/test_parsing/n_array_incomplete_invalid_value.json",
        "data/nst_json_testsuite/test_parsing/n_array_inner_array_no_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_invalid_utf8.json",
        "data/nst_json_testsuite/test_parsing/n_array_items_separated_by_semicolon.json",
        "data/nst_json_testsuite/test_parsing/n_array_just_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_just_minus.json",
        "data/nst_json_testsuite/test_parsing/n_array_missing_value.json",
        "data/nst_json_testsuite/test_parsing/n_array_newlines_unclosed.json",
        "data/nst_json_testsuite/test_parsing/n_array_number_and_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_number_and_several_commas.json",
        "data/nst_json_testsuite/test_parsing/n_array_spaces_vertical_tab_formfeed.json",
        "data/nst_json_testsuite/test_parsing/n_array_star_inside.json",
        "data/nst_json_testsuite/test_parsing/n_array_unclosed.json",
        "data/nst_json_testsuite/test_parsing/n_array_unclosed_trailing_comma.json",
        "data/nst_json_testsuite/test_parsing/n_array_unclosed_with_new_lines.json",
        "data/nst_json_testsuite/test_parsing/n_array_unclosed_with_object_inside.json",
        "data/nst_json_testsuite/test_parsing/n_incomplete_false.json",
        "data/nst_json_testsuite/test_parsing/n_incomplete_null.json",
        "data/nst_json_testsuite/test_parsing/n_incomplete_true.json",
        "data/nst_json_testsuite/test_parsing/n_number_++.json",
        "data/nst_json_testsuite/test_parsing/n_number_+1.json",
        "data/nst_json_testsuite/test_parsing/n_number_+Inf.json",
        "data/nst_json_testsuite/test_parsing/n_number_-01.json",
        "data/nst_json_testsuite/test_parsing/n_number_-1.0..json",
        "data/nst_json_testsuite/test_parsing/n_number_-2..json",
        "data/nst_json_testsuite/test_parsing/n_number_-NaN.json",
        "data/nst_json_testsuite/test_parsing/n_number_.-1.json",
        "data/nst_json_testsuite/test_parsing/n_number_.2e-3.json",
        "data/nst_json_testsuite/test_parsing/n_number_0.1.2.json",
        "data/nst_json_testsuite/test_parsing/n_number_0.3e+.json",
        "data/nst_json_testsuite/test_parsing/n_number_0.3e.json",
        "data/nst_json_testsuite/test_parsing/n_number_0.e1.json",
        "data/nst_json_testsuite/test_parsing/n_number_0e+.json",
        "data/nst_json_testsuite/test_parsing/n_number_0e.json",
        "data/nst_json_testsuite/test_parsing/n_number_0_capital_E+.json",
        "data/nst_json_testsuite/test_parsing/n_number_0_capital_E.json",
        "data/nst_json_testsuite/test_parsing/n_number_1.0e+.json",
        "data/nst_json_testsuite/test_parsing/n_number_1.0e-.json",
        "data/nst_json_testsuite/test_parsing/n_number_1.0e.json",
        "data/nst_json_testsuite/test_parsing/n_number_1eE2.json",
        "data/nst_json_testsuite/test_parsing/n_number_1_000.json",
        "data/nst_json_testsuite/test_parsing/n_number_2.e+3.json",
        "data/nst_json_testsuite/test_parsing/n_number_2.e-3.json",
        "data/nst_json_testsuite/test_parsing/n_number_2.e3.json",
        "data/nst_json_testsuite/test_parsing/n_number_9.e+.json",
        "data/nst_json_testsuite/test_parsing/n_number_expression.json",
        "data/nst_json_testsuite/test_parsing/n_number_hex_1_digit.json",
        "data/nst_json_testsuite/test_parsing/n_number_hex_2_digits.json",
        "data/nst_json_testsuite/test_parsing/n_number_Inf.json",
        "data/nst_json_testsuite/test_parsing/n_number_infinity.json",
        "data/nst_json_testsuite/test_parsing/n_number_invalid+-.json",
        "data/nst_json_testsuite/test_parsing/n_number_invalid-negative-real.json",
        "data/nst_json_testsuite/test_parsing/n_number_invalid-utf-8-in-bigger-int.json",
        "data/nst_json_testsuite/test_parsing/n_number_invalid-utf-8-in-exponent.json",
        "data/nst_json_testsuite/test_parsing/n_number_invalid-utf-8-in-int.json",
        "data/nst_json_testsuite/test_parsing/n_number_minus_infinity.json",
        "data/nst_json_testsuite/test_parsing/n_number_minus_sign_with_trailing_garbage.json",
        "data/nst_json_testsuite/test_parsing/n_number_minus_space_1.json",
        "data/nst_json_testsuite/test_parsing/n_number_NaN.json",
        "data/nst_json_testsuite/test_parsing/n_number_neg_int_starting_with_zero.json",
        "data/nst_json_testsuite/test_parsing/n_number_neg_real_without_int_part.json",
        "data/nst_json_testsuite/test_parsing/n_number_neg_with_garbage_at_end.json",
        "data/nst_json_testsuite/test_parsing/n_number_real_garbage_after_e.json",
        "data/nst_json_testsuite/test_parsing/n_number_real_without_fractional_part.json",
        "data/nst_json_testsuite/test_parsing/n_number_real_with_invalid_utf8_after_e.json",
        "data/nst_json_testsuite/test_parsing/n_number_starting_with_dot.json",
        //"data/nst_json_testsuite/test_parsing/n_number_then_00.json",   //正确的JSON
        "data/nst_json_testsuite/test_parsing/n_number_U+FF11_fullwidth_digit_one.json",
        "data/nst_json_testsuite/test_parsing/n_number_with_alpha.json",
        "data/nst_json_testsuite/test_parsing/n_number_with_alpha_char.json",
        "data/nst_json_testsuite/test_parsing/n_number_with_leading_zero.json",
        "data/nst_json_testsuite/test_parsing/n_object_bad_value.json",
        "data/nst_json_testsuite/test_parsing/n_object_bracket_key.json",
        "data/nst_json_testsuite/test_parsing/n_object_comma_instead_of_colon.json",
        "data/nst_json_testsuite/test_parsing/n_object_double_colon.json",
        "data/nst_json_testsuite/test_parsing/n_object_emoji.json",
        "data/nst_json_testsuite/test_parsing/n_object_garbage_at_end.json",
        "data/nst_json_testsuite/test_parsing/n_object_key_with_single_quotes.json",
        "data/nst_json_testsuite/test_parsing/n_object_missing_colon.json",
        "data/nst_json_testsuite/test_parsing/n_object_missing_key.json",
        "data/nst_json_testsuite/test_parsing/n_object_missing_semicolon.json",
        "data/nst_json_testsuite/test_parsing/n_object_missing_value.json",
        "data/nst_json_testsuite/test_parsing/n_object_no-colon.json",
        "data/nst_json_testsuite/test_parsing/n_object_non_string_key.json",
        "data/nst_json_testsuite/test_parsing/n_object_non_string_key_but_huge_number_instead.json",
        "data/nst_json_testsuite/test_parsing/n_object_pi_in_key_and_trailing_comma.json",
        "data/nst_json_testsuite/test_parsing/n_object_repeated_null_null.json",
        "data/nst_json_testsuite/test_parsing/n_object_several_trailing_commas.json",
        "data/nst_json_testsuite/test_parsing/n_object_single_quote.json",
        "data/nst_json_testsuite/test_parsing/n_object_trailing_comma.json",
        "data/nst_json_testsuite/test_parsing/n_object_trailing_comment.json",
        "data/nst_json_testsuite/test_parsing/n_object_trailing_comment_open.json",
        "data/nst_json_testsuite/test_parsing/n_object_trailing_comment_slash_open.json",
        "data/nst_json_testsuite/test_parsing/n_object_trailing_comment_slash_open_incomplete.json",
        "data/nst_json_testsuite/test_parsing/n_object_two_commas_in_a_row.json",
        "data/nst_json_testsuite/test_parsing/n_object_unquoted_key.json",
        "data/nst_json_testsuite/test_parsing/n_object_unterminated-value.json",
        "data/nst_json_testsuite/test_parsing/n_object_with_single_string.json",
        "data/nst_json_testsuite/test_parsing/n_object_with_trailing_garbage.json",
        //"data/nst_json_testsuite/test_parsing/n_single_space.json",     // 正确的JSON empty_t
        "data/nst_json_testsuite/test_parsing/n_string_1_surrogate_then_escape u.json",
        "data/nst_json_testsuite/test_parsing/n_string_1_surrogate_then_escape u1.json",
        "data/nst_json_testsuite/test_parsing/n_string_1_surrogate_then_escape u1x.json",
        "data/nst_json_testsuite/test_parsing/n_string_1_surrogate_then_escape.json",
        "data/nst_json_testsuite/test_parsing/n_string_accentuated_char_no_quotes.json",
        "data/nst_json_testsuite/test_parsing/n_string_backslash_00.json",
        "data/nst_json_testsuite/test_parsing/n_string_escaped_backslash_bad.json",
        "data/nst_json_testsuite/test_parsing/n_string_escaped_ctrl_char_tab.json",
        "data/nst_json_testsuite/test_parsing/n_string_escaped_emoji.json",
        "data/nst_json_testsuite/test_parsing/n_string_escape_x.json",
        "data/nst_json_testsuite/test_parsing/n_string_incomplete_escape.json",
        "data/nst_json_testsuite/test_parsing/n_string_incomplete_escaped_character.json",
        "data/nst_json_testsuite/test_parsing/n_string_incomplete_surrogate_escape_invalid.json",
        "data/nst_json_testsuite/test_parsing/n_string_invalid-utf-8-in-escape.json",
        "data/nst_json_testsuite/test_parsing/n_string_invalid_backslash_esc.json",
        "data/nst_json_testsuite/test_parsing/n_string_invalid_unicode_escape.json",
        //"data/nst_json_testsuite/test_parsing/n_string_invalid_utf-8.json",  // 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_invalid_utf8_after_escape.json",
        //"data/nst_json_testsuite/test_parsing/n_string_iso_latin_1.json",  //正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_leading_uescaped_thinspace.json",
        //"data/nst_json_testsuite/test_parsing/n_string_lone_utf8_continuation_byte.json", // 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_no_quotes_with_bad_escape.json",
        //"data/nst_json_testsuite/test_parsing/n_string_overlong_sequence_2_bytes.json",// 正确的JSON
        //"data/nst_json_testsuite/test_parsing/n_string_overlong_sequence_6_bytes.json",// 正确的JSON
        //"data/nst_json_testsuite/test_parsing/n_string_overlong_sequence_6_bytes_null.json",// 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_single_doublequote.json",
        "data/nst_json_testsuite/test_parsing/n_string_single_quote.json",
        "data/nst_json_testsuite/test_parsing/n_string_single_string_no_double_quotes.json",
        "data/nst_json_testsuite/test_parsing/n_string_start_escape_unclosed.json",
        //"data/nst_json_testsuite/test_parsing/n_string_unescaped_crtl_char.json",// 正确的JSON
        //"data/nst_json_testsuite/test_parsing/n_string_unescaped_newline.json",// 正确的JSON
        //"data/nst_json_testsuite/test_parsing/n_string_unescaped_tab.json",// 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_unicode_CapitalU.json",
        "data/nst_json_testsuite/test_parsing/n_string_UTF-16_incomplete_surrogate.json",
        //"data/nst_json_testsuite/test_parsing/n_string_UTF8_surrogate_U+D800.json",// 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_string_with_trailing_garbage.json",
        //"data/nst_json_testsuite/test_parsing/n_structure_100000_opening_arrays.json",  // 无法递归100000层
        "data/nst_json_testsuite/test_parsing/n_structure_3C.3E.json",
        "data/nst_json_testsuite/test_parsing/n_structure_3Cnull3E.json",
        "data/nst_json_testsuite/test_parsing/n_structure_array_trailing_garbage.json",
        "data/nst_json_testsuite/test_parsing/n_structure_array_with_extra_array_close.json",
        "data/nst_json_testsuite/test_parsing/n_structure_array_with_unclosed_string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_ascii-unicode-identifier.json",
        "data/nst_json_testsuite/test_parsing/n_structure_capitalized_True.json",
        "data/nst_json_testsuite/test_parsing/n_structure_close_unopened_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_comma_instead_of_closing_brace.json",
        "data/nst_json_testsuite/test_parsing/n_structure_double_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_end_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_incomplete_UTF8_BOM.json",
        "data/nst_json_testsuite/test_parsing/n_structure_lone-invalid-utf-8.json",
        "data/nst_json_testsuite/test_parsing/n_structure_lone-open-bracket.json",
        //"data/nst_json_testsuite/test_parsing/n_structure_no_data.json",// 正确的JSON
        "data/nst_json_testsuite/test_parsing/n_structure_null-byte-outside-string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_number_with_trailing_garbage.json",
        "data/nst_json_testsuite/test_parsing/n_structure_object_followed_by_closing_object.json",
        "data/nst_json_testsuite/test_parsing/n_structure_object_unclosed_no_value.json",
        "data/nst_json_testsuite/test_parsing/n_structure_object_with_comment.json",
        "data/nst_json_testsuite/test_parsing/n_structure_object_with_trailing_garbage.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_array_apostrophe.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_array_comma.json",
        //"data/nst_json_testsuite/test_parsing/n_structure_open_array_object.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_array_open_object.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_array_open_string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_array_string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object_close_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object_comma.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object_open_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object_open_string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_object_string_with_apostrophes.json",
        "data/nst_json_testsuite/test_parsing/n_structure_open_open.json",
        "data/nst_json_testsuite/test_parsing/n_structure_single_point.json",
        "data/nst_json_testsuite/test_parsing/n_structure_single_star.json",
        "data/nst_json_testsuite/test_parsing/n_structure_trailing_#.json",
        "data/nst_json_testsuite/test_parsing/n_structure_U+2060_word_joined.json",
        "data/nst_json_testsuite/test_parsing/n_structure_uescaped_LF_before_string.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unclosed_array.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unclosed_array_partial_null.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unclosed_array_unfinished_false.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unclosed_array_unfinished_true.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unclosed_object.json",
        "data/nst_json_testsuite/test_parsing/n_structure_unicode-identifier.json",
        "data/nst_json_testsuite/test_parsing/n_structure_UTF8_BOM_no_data.json",
        "data/nst_json_testsuite/test_parsing/n_structure_whitespace_formfeed.json",
        "data/nst_json_testsuite/test_parsing/n_structure_whitespace_U+2060_word_joiner.json"
    };
    
    std::vector<std::string> valid_json_files = {
        "data/nst_json_testsuite/test_parsing/y_array_arraysWithSpaces.json",
        "data/nst_json_testsuite/test_parsing/y_array_empty-string.json",
        "data/nst_json_testsuite/test_parsing/y_array_empty.json",
        "data/nst_json_testsuite/test_parsing/y_array_ending_with_newline.json",
        "data/nst_json_testsuite/test_parsing/y_array_false.json",
        "data/nst_json_testsuite/test_parsing/y_array_heterogeneous.json",
        "data/nst_json_testsuite/test_parsing/y_array_null.json",
        "data/nst_json_testsuite/test_parsing/y_array_with_1_and_newline.json",
        "data/nst_json_testsuite/test_parsing/y_array_with_leading_space.json",
        "data/nst_json_testsuite/test_parsing/y_array_with_several_null.json",
        "data/nst_json_testsuite/test_parsing/y_array_with_trailing_space.json",
        "data/nst_json_testsuite/test_parsing/y_number.json",
        "data/nst_json_testsuite/test_parsing/y_number_0e+1.json",
        "data/nst_json_testsuite/test_parsing/y_number_0e1.json",
        "data/nst_json_testsuite/test_parsing/y_number_after_space.json",
        "data/nst_json_testsuite/test_parsing/y_number_double_close_to_zero.json",
        //"data/nst_json_testsuite/test_parsing/y_number_double_huge_neg_exp.json",
        //"data/nst_json_testsuite/test_parsing/y_number_huge_exp.json",
        "data/nst_json_testsuite/test_parsing/y_number_int_with_exp.json",
        "data/nst_json_testsuite/test_parsing/y_number_minus_zero.json",
        "data/nst_json_testsuite/test_parsing/y_number_negative_int.json",
        "data/nst_json_testsuite/test_parsing/y_number_negative_one.json",
        "data/nst_json_testsuite/test_parsing/y_number_negative_zero.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_capital_e.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_capital_e_neg_exp.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_capital_e_pos_exp.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_exponent.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_fraction_exponent.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_neg_exp.json",
        //"data/nst_json_testsuite/test_parsing/y_number_real_neg_overflow.json",
        "data/nst_json_testsuite/test_parsing/y_number_real_pos_exponent.json",
        //"data/nst_json_testsuite/test_parsing/y_number_real_pos_overflow.json",
        //"data/nst_json_testsuite/test_parsing/y_number_real_underflow.json",
        "data/nst_json_testsuite/test_parsing/y_number_simple_int.json",
        "data/nst_json_testsuite/test_parsing/y_number_simple_real.json",
        "data/nst_json_testsuite/test_parsing/y_number_too_big_neg_int.json",
        "data/nst_json_testsuite/test_parsing/y_number_too_big_pos_int.json",
        "data/nst_json_testsuite/test_parsing/y_number_very_big_negative_int.json",
        "data/nst_json_testsuite/test_parsing/y_object.json",
        "data/nst_json_testsuite/test_parsing/y_object_basic.json",
        "data/nst_json_testsuite/test_parsing/y_object_duplicated_key.json",
        "data/nst_json_testsuite/test_parsing/y_object_duplicated_key_and_value.json",
        "data/nst_json_testsuite/test_parsing/y_object_empty.json",
        "data/nst_json_testsuite/test_parsing/y_object_empty_key.json",
        "data/nst_json_testsuite/test_parsing/y_object_escaped_null_in_key.json",
        "data/nst_json_testsuite/test_parsing/y_object_extreme_numbers.json",
        "data/nst_json_testsuite/test_parsing/y_object_long_strings.json",
        "data/nst_json_testsuite/test_parsing/y_object_simple.json",
        "data/nst_json_testsuite/test_parsing/y_object_string_unicode.json",
        "data/nst_json_testsuite/test_parsing/y_object_with_newlines.json",
        "data/nst_json_testsuite/test_parsing/y_string_1_2_3_bytes_UTF-8_sequences.json",
        "data/nst_json_testsuite/test_parsing/y_string_accepted_surrogate_pair.json",
        "data/nst_json_testsuite/test_parsing/y_string_accepted_surrogate_pairs.json",
        "data/nst_json_testsuite/test_parsing/y_string_allowed_escapes.json",
        "data/nst_json_testsuite/test_parsing/y_string_backslash_and_u_escaped_zero.json",
        "data/nst_json_testsuite/test_parsing/y_string_backslash_doublequotes.json",
        "data/nst_json_testsuite/test_parsing/y_string_comments.json",
        "data/nst_json_testsuite/test_parsing/y_string_double_escape_a.json",
        "data/nst_json_testsuite/test_parsing/y_string_double_escape_n.json",
        "data/nst_json_testsuite/test_parsing/y_string_escaped_control_character.json",
        "data/nst_json_testsuite/test_parsing/y_string_escaped_noncharacter.json",
        "data/nst_json_testsuite/test_parsing/y_string_in_array.json",
        "data/nst_json_testsuite/test_parsing/y_string_in_array_with_leading_space.json",
        "data/nst_json_testsuite/test_parsing/y_string_last_surrogates_1_and_2.json",
        "data/nst_json_testsuite/test_parsing/y_string_newline_uescaped.json",
        "data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+10FFFF.json",
        "data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+1FFFF.json",
        "data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+FFFF.json",
        "data/nst_json_testsuite/test_parsing/y_string_null_escape.json",
        "data/nst_json_testsuite/test_parsing/y_string_one-byte-utf-8.json",
        "data/nst_json_testsuite/test_parsing/y_string_pi.json",
        "data/nst_json_testsuite/test_parsing/y_string_simple_ascii.json",
        "data/nst_json_testsuite/test_parsing/y_string_space.json",
        "data/nst_json_testsuite/test_parsing/y_string_three-byte-utf-8.json",
        "data/nst_json_testsuite/test_parsing/y_string_two-byte-utf-8.json",
        "data/nst_json_testsuite/test_parsing/y_string_u+2028_line_sep.json",
        "data/nst_json_testsuite/test_parsing/y_string_u+2029_par_sep.json",
        "data/nst_json_testsuite/test_parsing/y_string_uEscape.json",
        "data/nst_json_testsuite/test_parsing/y_string_unescaped_char_delete.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicode.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicodeEscapedBackslash.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicode_2.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicode_escaped_double_quote.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicode_U+200B_ZERO_WIDTH_SPACE.json",
        "data/nst_json_testsuite/test_parsing/y_string_unicode_U+2064_invisible_plus.json",
        "data/nst_json_testsuite/test_parsing/y_string_UTF-16_Surrogates_U+1D11E_MUSICAL_SYMBOL_G_CLEF.json",
        //"data/nst_json_testsuite/test_parsing/y_string_utf16.json",
        "data/nst_json_testsuite/test_parsing/y_string_utf8.json",
        "data/nst_json_testsuite/test_parsing/y_string_with_del_character.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_false.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_int.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_negative_real.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_null.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_string.json",
        "data/nst_json_testsuite/test_parsing/y_structure_lonely_true.json",
        "data/nst_json_testsuite/test_parsing/y_structure_string_empty.json",
        "data/nst_json_testsuite/test_parsing/y_structure_trailing_newline.json",
        "data/nst_json_testsuite/test_parsing/y_structure_true_in_array.json",
        "data/nst_json_testsuite/test_parsing/y_structure_whitespace_array.json"
    };
    
    /*amo::path root(
        R"(data/nst_json_testsuite/test_parsing)");
    std::cout << "{\n";
    
    for (auto& p : root) {
        std::cout << "\"data/nst_json_testsuite/test_parsing/" << p.filename().string() << "\"," << std::endl;
    }
    
    std::cout << "};";*/
    
    for (auto& p : error_json_files) {
        //std::cout << "parse file: " << p << std::endl;
        json_type json = amo::file_reader{ p };
        
        if (json.is_valid()) {
            std::cout << "parse file: " << p << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), false);
    }
    
    for (auto& p : valid_json_files) {
        //std::cout << "parse file: " << p << std::endl;
        json_type json = amo::file_reader{ p };
        
        if (!json.is_valid()) {
            std::cout << "parse file: " << p << std::endl;
        }
        
        EXPECT_EQ(json.is_valid(), true);
    }
}