#include "WorldTransform.h"

#include "MakeMatrixMath.h"

#include "imgui.h"

#include "algorithm"

void WorldTransform::Initialize() {

	translate_ = { 0.0f,0.0f,0.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	scale_ = { 1.0f,1.0f,1.0f };

	velocity_ = { 0.0f,0.0f,0.0f };

	offset_ = { 0.0f,0.0f,0.0f };

	isClamp_ = false;

	max_ = { 0.0f,0.0f,0.0f };
	min_ = { 0.0f,0.0f,0.0f };

	UpdateMatrix();
}

void WorldTransform::UpdateMatrix() {

	translate_ += velocity_;

	if (isClamp_) {

		translate_ = {
			std::clamp(translate_.x,min_.x,max_.x),
			std::clamp(translate_.y,min_.y,max_.y),
			std::clamp(translate_.z,min_.z,max_.z)
		};
	}

	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_ + offset_);

	if (parent_) {

		worldMatrix_ *= parent_->GetWorldMatrix();
	}

	velocity_ = { 0.0f,0.0f,0.0f };
}

void WorldTransform::DisplayImGui() {

	if (ImGui::TreeNode("WorldTransform")) {

		ImGui::DragFloat3("translate", &translate_.x, 0.1f);
		ImGui::DragFloat3("rotate", &rotate_.x, 0.01f);
		ImGui::DragFloat3("scale", &scale_.x, 0.1f);

		ImGui::TreePop();
	}

}

const Vector3& WorldTransform::GetWorldTranslate() const {

	Vector3 result;

	result.x = worldMatrix_.m[3][0];
	result.y = worldMatrix_.m[3][1];
	result.z = worldMatrix_.m[3][2];

	return result;
}

void WorldTransform::SetParent(WorldTransform* parent) {

	this->Initialize();

	this->parent_ = parent;
}