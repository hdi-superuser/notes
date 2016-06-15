$(document).ready(function () {
	$('.post-delete').click(function () {
		var clickedElement = $(this);
		$('#post-delete-confirm-dialog').dialog({
			buttons: {
				'OK': function () {
					window.location = '/forum/{post_id}/post_delete'.supplant({
						'post_id': clickedElement.attr('post-id')
					});
				},
				'Cancel': function() {
					$(this).dialog('close');
				}
			}
		});
	});

	// Move the reply form around when user clicks on "Reply"
	$('.post-reply').click(function () {
		// Set which post we're replying to
		var element = $(this);
		$('#id_parent').val(element.attr('post-id'));

		// Hide form & removes old instance of CKEditor
		var postReplyFormDiv = $('#post-reply-form-div');
		postReplyFormDiv.hide();
		// Remove this instance
		CKEDITOR.remove(CKEDITOR.instances['id_content']);
		// And also remove it from DOM
		$('#cke_id_content').remove();

		// Move the element around
		var postForm = $('#post-reply-form');
		postForm.attr('action', element.attr('post-reply-url'));
		console.log('new path = ' + postForm.attr('action'));
		$('#post-' + element.attr('post-id')).parent().after(postForm.parent());

		// Show form & add CKEditor
		postReplyFormDiv.show();
		CKEDITOR.replace('id_content');
	});
});