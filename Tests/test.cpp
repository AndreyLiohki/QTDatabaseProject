#include "pch.h"
#include "Header.h"

TEST(Validator, validate_login) {
	Validator v;
	EXPECT_TRUE(v.validLogin(std::string("vika66")));
	EXPECT_FALSE(v.validLogin(std::string("!Vika66")));
}
TEST(Validator, validate_pass) {
	Validator vo;
	EXPECT_TRUE(vo.validPassword(std::string("Vi123456")));
	EXPECT_FALSE(vo.validPassword(std::string("1234")));
}